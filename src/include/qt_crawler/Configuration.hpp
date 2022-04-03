//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include <memory>
#include <optional>
#include <string_view>

/**
 * @brief Configuration interface 
 * Exposed for unit tests
 */
class Configuration {
public:
    virtual ~Configuration() = default;
    virtual bool HasKey(std::string_view const key) const noexcept = 0;
    virtual std::optional<std::string> GetValue(std::string_view const key) const noexcept = 0;
    virtual std::string Help() const noexcept = 0;
};

class ConfigurationImpl : public Configuration {
public:
    explicit ConfigurationImpl(int argc, char *argv[]) noexcept;
    ~ConfigurationImpl() noexcept override;
    ConfigurationImpl(const ConfigurationImpl &) = delete;
    ConfigurationImpl &operator=(const ConfigurationImpl &) = delete;

    bool HasKey(std::string_view const key) const noexcept override;
    std::optional<std::string> GetValue(std::string_view const key) const noexcept override;
    std::string Help() const noexcept override;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};


class ConfigurationFactory {
public:
    using created_type = Configuration;
    using created_type_p = std::unique_ptr<created_type>;
    using concrete_created_type = ConfigurationImpl;

    ~ConfigurationFactory() = default;
    created_type_p Create(int argc, char *argv[]) const {
        return std::make_unique<concrete_created_type>(argc, argv);
    }
};