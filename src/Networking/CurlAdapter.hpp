//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Networking/HtmlProvider.hpp"

#include <string>
BEGIN_QTC_NAMESPACE

/**
 * @brief RAII Curl wrapper which allows to get contents of web page
 * @see HtmlProvider
 * @warning Get is not thread safe method
 */
class CurlAdapter : public HtmlProvider {

public:
    explicit CurlAdapter();
    ~CurlAdapter() override;
    Response Get(std::string const &url) override;
    Response ValidateUrl(std::string const &url) override;
    std::optional<std::string> NormalizeUrl(std::string const &rootUrl, std::string const &maybeUrl) override;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

class CurlAdapterFactory : public HtmlProviderFactory {
public:
    using concrete_created_type = CurlAdapter;

    ~CurlAdapterFactory() override = default;
    created_type_p Create() const override {
        return std::make_unique<concrete_created_type>();
    }
};

END_QTC_NAMESPACE