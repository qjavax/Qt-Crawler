#include "CurlAdapter.hpp"

#include <curl/curl.h>

namespace {
USING_QTC_NAMESPACE

struct MemoryStruct {
    char *buffer;
    size_t size;

    MemoryStruct() {
        this->buffer = new char;
        this->size = 0;
    }
    ~MemoryStruct() {
        delete buffer;
    }
};

size_t write_data(void *contents, size_t sz, size_t nmemb, void *ctx) {
    size_t realsize = sz * nmemb;
    struct MemoryStruct *mem = reinterpret_cast<MemoryStruct *>(ctx);

    void *ptr = realloc(mem->buffer, mem->size + realsize);
    if (!ptr) {
        /* out of memory */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->buffer = reinterpret_cast<char *>(ptr);
    memcpy(&(mem->buffer[mem->size]), contents, realsize);
    mem->size += realsize;
    return realsize;
}
} // namespace

struct CurlAdapter::Impl {
    explicit Impl() {
        handle = curl_multi_init();
        /* Important: use HTTP2 over HTTPS */
        curl_easy_setopt(handle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
        /* buffer body */
        mem = std::make_unique<MemoryStruct>();
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, mem.get());
        curl_easy_setopt(handle, CURLOPT_PRIVATE, mem.get());

        curl_easy_setopt(handle, CURLOPT_ACCEPT_ENCODING, "");
        curl_easy_setopt(handle, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 10L);
        curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, 2L);
        curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "");
        curl_easy_setopt(handle, CURLOPT_FILETIME, 1L);
        curl_easy_setopt(handle, CURLOPT_USERAGENT, "Http client");
        curl_easy_setopt(handle, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_easy_setopt(handle, CURLOPT_UNRESTRICTED_AUTH, 1L);
        curl_easy_setopt(handle, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
        curl_easy_setopt(handle, CURLOPT_EXPECT_100_TIMEOUT_MS, 0L);
    }
    ~Impl() {
     //   curl_easy_cleanup(handle);
    }
    CurlAdapter::Response Get(std::string const &url) {
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

        CURLcode res = curl_easy_perform(handle);

        if (res != CURLE_OK) {
            return Response(Result(Result::Success::No, curl_easy_strerror(res)));
        }
        return Response(Result(Result::Success::Yes), mem->buffer);
    }

  private:
    CURL *handle;
    std::unique_ptr<MemoryStruct> mem;
};

CurlAdapter::CurlAdapter() : _impl(std::make_unique<Impl>()) {}

CurlAdapter::~CurlAdapter() = default;

CurlAdapter::Response CurlAdapter::Get(std::string const &url) {
    return _impl->Get(url);
}
