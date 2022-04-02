//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include <string_view>

struct ConfigurationKeys {

    // For short keys
    struct ShortKey {
        constexpr static std::string_view help{"h"};
        constexpr static std::string_view url{"u"};
    };

    // For long keys
    struct Key {
        constexpr static std::string_view help{"help"};
        constexpr static std::string_view url{"url"};
        constexpr static std::string_view outDir{"out"};
    };

    // For const values
    struct Value {};
};
