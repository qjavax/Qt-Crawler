#include "include/qt_crawler/QtCrawlerApp.hpp"

#include "Common/Namespace.h"
#include "Common/Types.h"
#include "Common/ExceptionHandler.h"

#include "Networking/CurlAdapter.hpp"
#include "Networking/HttpClient.hpp"

#include "Parser/GumboParserAdapter.hpp"

namespace {
USING_QTC_NAMESPACE
}
struct QtCrawlerApp::Impl {
    explicit Impl(Configuration &&config) noexcept : _config(std::move(config)) {
        TRY CATCH_STD CATCH_ALL
    }
    ~Impl() noexcept = default;

    private:
    Configuration &&_config;
};


QtCrawlerApp::QtCrawlerApp(Configuration &&config) noexcept
    : _impl(std::make_unique<Impl>(std::move(config))) {}

QtCrawlerApp::~QtCrawlerApp() noexcept = default;

int QtCrawlerApp::Run() noexcept {
    TRY return 0; CATCH_STD CATCH_ALL
    return -1;
}
