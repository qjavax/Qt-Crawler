#include "include/qt_crawler/QtCrawlerApp.hpp"
#include "include/qt_crawler/ConfigurationKeys.hpp"

#include "Common/ExceptionHandler.h"
#include "Common/Namespace.h"
#include "Common/Types.h"

#include "IO/FileSystemWriter.hpp"

#include "Networking/CurlAdapter.hpp"
#include "Networking/HttpClient.hpp"

#include "Parser/GumboParserAdapter.hpp"

namespace {
USING_QTC_NAMESPACE
}
struct QtCrawlerApp::Impl {
    explicit Impl(std::unique_ptr<Configuration> config) noexcept
        : _config(std::move(config)) {}
    Result Init() {
        if (auto result = this->CheckAllRequiredArgs(); !result) {
            return result;
        }
        auto url = _config->GetValue(ConfigurationKeys::Key::url);

        auto htmlProviderFactory = std::make_shared<CurlAdapterFactory>();
        std::shared_ptr<HtmlParser> gumboHtmlParser = GumboParserAdapterFactory().Create();
        auto httpClientFactory = std::make_unique<HttpClientFactory>(htmlProviderFactory, gumboHtmlParser);
        _httpClient = httpClientFactory->Create(*url);

        return Result(Result::Success::Yes);
    }
    Result Run() {
        auto outDir = _config->GetValue(ConfigurationKeys::Key::outDir);

        std::shared_ptr<Writer<std::string>> writer = FileSystemWriterFactory().Create(*outDir);
        if (auto result = _httpClient->VisitAndSaveAllSubpages(std::move(writer)); !result) {
            return result;
        }
        return Result(Result::Success::Yes);
    }

    ~Impl() noexcept = default;

private:
    Result CheckAllRequiredArgs() {
        Result::Success success{Result::Success::Yes};
        std::string reason;

        auto url = _config->GetValue(ConfigurationKeys::Key::url);
        if (!url) {
            success = Result::Success::No;
            reason.append(std::string("Missing required cmd argument: ") + ConfigurationKeys::Key::url.data() + '\n');
        }
        auto outDir = _config->GetValue(ConfigurationKeys::Key::outDir);
        if (!outDir) {
            success = Result::Success::No;
            reason.append(std::string("Missing required cmd argument: ") + ConfigurationKeys::Key::outDir.data() + '\n');
        }
        return Result{success, reason};
    }

    std::unique_ptr<Configuration> _config;
    std::unique_ptr<Client> _httpClient;
};


QtCrawlerApp::QtCrawlerApp(std::unique_ptr<Configuration> config) noexcept
    : _impl(std::make_unique<Impl>(std::move(config))) {}

QtCrawlerApp::~QtCrawlerApp() noexcept = default;

Result QtCrawlerApp::Run() noexcept {
    TRY if (auto result = _impl->Init(); !result) {
        return result;
    }
    return _impl->Run();
    CATCH_STD CATCH_ALL return Result(Result::Success::No, "Exception encountered");
}
