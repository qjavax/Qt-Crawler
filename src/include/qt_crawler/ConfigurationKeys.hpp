//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include <string_view>

struct ConfigurationKeys {

    struct ShortKey {
        constexpr static std::string_view help{"h"};
        constexpr static std::string_view url{"u"};
    };

    struct Key {
        constexpr static std::string_view help{"help"};
        constexpr static std::string_view url{"url"};
    };

    struct Value {};
};
