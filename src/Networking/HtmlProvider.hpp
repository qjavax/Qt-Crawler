//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"

#include <string>
BEGIN_QTC_NAMESPACE

class HtmlProvider {
public:
    struct Response {
        Result result;
        std::optional<std::string> data;

        Response(Result const &_result, std::string const &_data = "")
            : result(std::move(_result))
            , data(std::move(_data)) {}
    };
    virtual ~HtmlProvider() = default;
    virtual Response Get(std::string const &url) = 0;
    virtual Response ValidateUrl(std::string const &url) = 0;
    virtual std::optional<std::string> NormalizeUrl(std::string const &rootUrl, std::string const &maybeUrl) = 0;
};

class HtmlProviderFactory {
public:
    using created_type = HtmlProvider;
    using created_type_p = std::unique_ptr<created_type>;

    virtual ~HtmlProviderFactory() = default;
    virtual created_type_p Create() const = 0;
};

END_QTC_NAMESPACE