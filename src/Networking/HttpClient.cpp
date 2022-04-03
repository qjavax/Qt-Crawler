#include "HttpClient.hpp"

#include <algorithm>
#include <curl/curl.h>
#include <fmt/color.h>
#include <fmt/core.h>

namespace {
USING_QTC_NAMESPACE

std::string getUIDFromUrl(std::string const &url) {
    auto res = url.substr(url.find("://") + 3);
    std::replace(res.begin(), res.end(), '/', '_');
    if (res.back() == '_') {
        res.pop_back();
    }
    if (res.rfind(".html") != res.length() - 5) {
        res.append(".html");
    }
    return res;
}
} // namespace

struct HttpClient::Impl {
    explicit Impl(std::shared_ptr<HtmlProviderFactory> htmlProviderFactory, std::shared_ptr<HtmlParser> htmlParser,
                  std::string const &url)
        : _htmlProviderFactory(std::move(htmlProviderFactory))
        , _htmlParser(std::move(htmlParser))
        , _rootUrl(std::move(url)) {
        if (curl_global_init(CURL_GLOBAL_ALL)) {
            throw std::runtime_error("Cannot initialize curl");
        }
    }
    ~Impl() {
        curl_global_cleanup();
    }
    Result VisitAndSaveAllSubpages(std::shared_ptr<Writer<std::string>> writer) {
        if (auto result = this->VisitRootPage(writer); !result) {
            return result;
        }
        auto subPages = _htmlParser->GetAllLinks();
        for (const auto &page : subPages) {
            if (auto response = this->VisitPage(page, writer); !response.result) {
                fmt::print(stderr, fg(fmt::color::red), "Visiting subpage url {} failed: {} \n", page,
                           response.result.what());
            }
        }
        return Result(Result::Success::Yes);
    }

private:
    Result VisitRootPage(std::shared_ptr<Writer<std::string>> writer) {
        auto response = this->VisitPage(_rootUrl, writer);
        if (response.result && response.data) {
            if (auto parsingResult = _htmlParser->Parse(*response.data); !parsingResult) {
                return parsingResult;
            }
            return Result(Result::Success::Yes);
        }
        return Result(Result::Success::No, response.result.what());
    }

    HtmlProvider::Response VisitPage(std::string const &url, std::shared_ptr<Writer<std::string>> &writer) {
        auto htmlProvider = _htmlProviderFactory->Create();
        auto maybeUrl = htmlProvider->NormalizeUrl(_rootUrl, url);
        if (!maybeUrl) {
            return HtmlProvider::Response(Result(Result::Success::No, fmt::format("{} is not valid url", url)));
        }
        if (auto response = htmlProvider->ValidateUrl(*maybeUrl); !response.result) {
            return response;
        }
        auto response = htmlProvider->Get(*maybeUrl);
        if (response.result && response.data && !response.data->empty()) {
            response.result = writer->Write(*response.data, getUIDFromUrl(*maybeUrl));
        }
        return response;
    }

private:
    std::shared_ptr<HtmlProviderFactory> _htmlProviderFactory;
    std::shared_ptr<HtmlParser> _htmlParser;
    std::string const _rootUrl;
};

HttpClient::HttpClient(std::shared_ptr<HtmlProviderFactory> htmlProviderFactory, std::shared_ptr<HtmlParser> htmlParser,
                       std::string const &url)
    : _impl(std::make_unique<Impl>(std::move(htmlProviderFactory), std::move(htmlParser), std::move(url))) {}

HttpClient::~HttpClient() = default;

Result HttpClient::VisitAndSaveAllSubpages(std::shared_ptr<Writer<std::string>> writer) {
    return _impl->VisitAndSaveAllSubpages(std::move(writer));
}