#include "include/qt_crawler/Configuration.hpp"
#include "include/qt_crawler/ConfigurationKeys.hpp"

#include "Common/ExceptionHandler.h"
#include "Common/Namespace.h"
#include "Common/Types.h"
#include <cxxopts.hpp>

struct Configuration::Impl {
    explicit Impl(int argc, char *argv[]) noexcept {
        TRY using ShortKey = ConfigurationKeys::ShortKey;
        using Key = ConfigurationKeys::Key;
        std::string help = ShortKey::help.data() + std::string(",") + Key::help.data();
        std::string url = ShortKey::url.data() + std::string(",") + Key::url.data();

        _options = std::make_unique<cxxopts::Options>("qt_crawler", "QT Documentation Crawler");
        _options->add_options()(help, "Show help.", cxxopts::value<bool>()->default_value("false"));
        _options->add_options()(url, "Url to start crawler from", cxxopts::value<std::string>());
        parsedOpts = std::make_unique<cxxopts::ParseResult>(_options->parse(argc, argv));
        CATCH_STD
        CATCH_ALL
    }
    bool HasKey(std::string_view const key) const {
        return parsedOpts->count(std::string(key));
    }
    std::optional<std::string> GetValue(std::string_view const key) const {
        std::optional<std::string> result = std::nullopt;
        auto strKey = std::string(key);
        if (parsedOpts->count(strKey)) {
            result = (*parsedOpts)[strKey].as<std::string>();
        }
        return result;
    }

    std::string Help() const {
        return _options->help();
    }

private:
    std::unique_ptr<cxxopts::Options> _options;
    std::unique_ptr<cxxopts::ParseResult> parsedOpts;
};


Configuration::Configuration(int argc, char *argv[]) noexcept
    : _impl(std::make_unique<Impl>(argc, argv)) {}

Configuration::~Configuration() noexcept = default;

bool Configuration::HasKey(std::string_view const key) const noexcept {
    TRY return _impl->HasKey(key);
    CATCH_STD
    CATCH_ALL
    return false;
}

std::optional<std::string> Configuration::GetValue(std::string_view const key) const noexcept {
    TRY return _impl->GetValue(key);
    CATCH_STD
    CATCH_ALL
    return std::nullopt;
}

std::string Configuration::Help() const noexcept {
    TRY return _impl->Help();
    CATCH_STD
    CATCH_ALL
    return "";
}