#include "HttpClient.hpp"

#include <curl/curl.h>


namespace {
USING_QTC_NAMESPACE

} // namespace

struct HttpClient::Impl {
    explicit Impl(std::shared_ptr<NetworkingProviderFactory> networkingProviderFactory, std::string const &host)
        : _networkingProviderFactory(std::move(networkingProviderFactory))
        , _host(std::move(host)) {
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
    std::string const _host;
};

HttpClient::HttpClient(std::shared_ptr<NetworkingProviderFactory> networkingProviderFactory, std::string const &host)
    : _impl(std::make_unique<Impl>(std::move(networkingProviderFactory), std::move(host))) {}

HttpClient::~HttpClient() = default;
