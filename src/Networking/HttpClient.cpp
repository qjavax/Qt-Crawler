#include "HttpClient.hpp"

#include <curl/curl.h>


namespace {
USING_QTC_NAMESPACE

} // namespace

struct HttpClient::Impl {
    explicit Impl(std::shared_ptr<NetworkingProviderFactory> networkingProviderFactory,
                  std::shared_ptr<HtmlParser> htmlParser, std::string const &url)
        : _networkingProviderFactory(std::move(networkingProviderFactory))
        , _htmlParser(std::move(htmlParser))
        , _url(std::move(url)) {
        if (curl_global_init(CURL_GLOBAL_ALL)) {
            throw std::runtime_error("Cannot initialize curl");
        }
    }
    ~Impl() {
        // Experimental disable
        // curl_global_cleanup();
    }

private:
    std::shared_ptr<NetworkingProviderFactory> _networkingProviderFactory;
    std::shared_ptr<HtmlParser> _htmlParser;
    std::string const _url;
};

HttpClient::HttpClient(std::shared_ptr<NetworkingProviderFactory> networkingProviderFactory,
                       std::shared_ptr<HtmlParser> htmlParser, std::string const &url)
    : _impl(std::make_unique<Impl>(std::move(networkingProviderFactory), std::move(htmlParser), std::move(url))) {}

HttpClient::~HttpClient() = default;
