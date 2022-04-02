//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"

#include <string>
BEGIN_QTC_NAMESPACE

class NetworkingProvider {
public:
    struct Response {
        Result result;
        std::optional<std::string> data;

        Response(Result const &_result, std::string const &_data = "")
            : result(std::move(_result))
            , data(std::move(_data)) {}
    };
    virtual ~NetworkingProvider() = default;
    virtual Response Get(std::string const &url) = 0;
};

class NetworkingProviderFactory {
public:
    using created_type = NetworkingProvider;
    using created_type_p = std::unique_ptr<created_type>;

    virtual ~NetworkingProviderFactory() = default;
    virtual created_type_p Create() const = 0;
};

END_QTC_NAMESPACE