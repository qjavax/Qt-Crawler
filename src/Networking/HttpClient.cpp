#include "HttpClient.hpp"

#include <curl/curl.h>


namespace {
USING_QTC_NAMESPACE

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
        // Experimental disable
        // curl_global_cleanup();
    }
    Result VisitAndSaveAllSubpages(std::shared_ptr<Writer<std::string>> writer) {
        if (auto result = this->VisitRootPage(writer); !result) {
            return Result(Result::Success::No, "Parsing root url failed");
        }
        auto subPages = _htmlParser->GetAllLinks();
        for (const auto &page : subPages) {
            if (auto response = this->VisitPage(page, writer); !response.result) {
                return Result(Result::Success::No, "Parsing subpage url failed: " + page);
            }
        }
        return Result(Result::Success::Yes);
    }

private:
    Result VisitRootPage(std::shared_ptr<Writer<std::string>> writer) {
        auto response = this->VisitPage(_rootUrl, writer);
        if (response.result && response.data) {
            auto parsingResult = _htmlParser->Parse(*response.data);
            return Result(Result::Success::Yes);
        }
        return Result(Result::Success::No);
    }

    HtmlProvider::Response VisitPage(std::string const &url, std::shared_ptr<Writer<std::string>> &writer) {
        auto htmlProvider = _htmlProviderFactory->Create();
        auto response = htmlProvider->Get(url);
        if (response.result && response.data) {
            _writer->Write(*response.data, "definetly_not_here");
        }
        return response;
    }

private:
    std::shared_ptr<HtmlProviderFactory> _htmlProviderFactory;
    std::shared_ptr<HtmlParser> _htmlParser;
    std::shared_ptr<Writer<std::string>> _writer;
    std::string const _rootUrl;
};

HttpClient::HttpClient(std::shared_ptr<HtmlProviderFactory> htmlProviderFactory, std::shared_ptr<HtmlParser> htmlParser,
                       std::string const &url)
    : _impl(std::make_unique<Impl>(std::move(htmlProviderFactory), std::move(htmlParser), std::move(url))) {}

HttpClient::~HttpClient() = default;

Result HttpClient::VisitAndSaveAllSubpages(std::shared_ptr<Writer<std::string>> writer) {
    return _impl->VisitAndSaveAllSubpages(std::move(writer));
}