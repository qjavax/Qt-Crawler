#include "CurlAdapter.hpp"

#include <curl/curl.h>

#include <algorithm>
#include <vector>

namespace {
USING_QTC_NAMESPACE

struct MemoryStruct {
    std::vector<char> buffer;
};

size_t write_data(void *contents, size_t sz, size_t nmemb, void *ctx) {
    assert(sz == sizeof(char));
    struct MemoryStruct *mem = reinterpret_cast<MemoryStruct *>(ctx);

    mem->buffer.resize(mem->buffer.size() + nmemb);

    std::copy_n(reinterpret_cast<char *>(contents), nmemb, std::back_inserter(mem->buffer));
    return sz * nmemb;
}
} // namespace

struct CurlAdapter::Impl {
    explicit Impl() {
        handle = curl_easy_init();
        if (handle) {
            mem = std::make_unique<MemoryStruct>();
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, mem.get());
            curl_easy_setopt(handle, CURLOPT_PRIVATE, mem.get());

            curl_easy_setopt(handle, CURLOPT_TIMEOUT, 5L);
            curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 10L);
            curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 5L);
        }
    }
    ~Impl() {
        curl_easy_cleanup(handle);
    }
    CurlAdapter::Response Get(std::string const &url) {
        if (!handle) {
            return Response(Result(Result::Success::No, "Curl is not initialized"));
        }
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

        CURLcode res = curl_easy_perform(handle);

        if (res != CURLE_OK) {
            return Response(Result(Result::Success::No, curl_easy_strerror(res)));
        }

        return Response(Result(Result::Success::Yes), std::string(mem->buffer.begin(), mem->buffer.end()));
    }
    CurlAdapter::Response ValidateUrl(std::string const &url) {
        CURLUcode urlCode;

        CURLU *urlHandler = curl_url();
        if (!urlHandler) {
            return Response(Result(Result::Success::No, "Could not create url handler"));
        }
        urlCode = curl_url_set(urlHandler, CURLUPART_URL, url.c_str(), 0);

        curl_url_cleanup(urlHandler);
        if (urlCode) {
            return Response(Result(Result::Success::No, "Given string is not valid url: " + url));
        }
        return Response(Result(Result::Success::Yes));
    }

private:
    CURL *handle;
    std::unique_ptr<MemoryStruct> mem;
};

CurlAdapter::CurlAdapter()
    : _impl(std::make_unique<Impl>()) {}

CurlAdapter::~CurlAdapter() = default;

CurlAdapter::Response CurlAdapter::Get(std::string const &url) {
    return _impl->Get(url);
}

CurlAdapter::Response CurlAdapter::ValidateUrl(std::string const &url) {
    return _impl->ValidateUrl(url);
}

std::optional<std::string> CurlAdapter::NormalizeUrl(std::string const &rootUrl, std::string const &maybeUrl) {
    // Assume valid and absolute url
    if (maybeUrl.find("://") != std::string::npos) {
        return maybeUrl;
    }
    std::optional<std::string> str = std::nullopt;
    // Ignore anachors
    if (maybeUrl.front() == '#') {
        return str;
    }
    // releative to root url
    else if (maybeUrl.find('/') == std::string::npos) {
        str = rootUrl.substr(0, rootUrl.rfind('/') + 1) + maybeUrl;
    }
    // Case for non specified protocol
    else if (maybeUrl.find("//") == 0) {
        str = rootUrl.substr(0, rootUrl.find("://") + 1) + maybeUrl;
    }
    return str;
}
