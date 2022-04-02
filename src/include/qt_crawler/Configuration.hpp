//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include <memory>
#include <optional>
#include <string_view>

class Configuration {
public:
    explicit Configuration(int argc, char *argv[]) noexcept;
    ~Configuration() noexcept;
    Configuration(const Configuration &) = delete;
    Configuration &operator=(const Configuration &) = delete;

    bool HasKey(std::string_view const key) const noexcept;
    std::optional<std::string> GetValue(std::string_view const key) const noexcept;
    std::string Help() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};