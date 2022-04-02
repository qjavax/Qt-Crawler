//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once

#include <optional>
#include <string>

struct Result {
    enum class Success : bool { No = 0, Yes };
    Success success;
    std::optional<std::string> reason;

    Result(Success const _success, std::optional<std::string> const &_reason = std::nullopt)
        : success(_success)
        , reason(std::move(_reason)) {}
    constexpr operator bool() const noexcept {
        return success == Success::Yes;
    }
    const std::string what() const noexcept {
        return reason ? *reason : "";
    }
};
