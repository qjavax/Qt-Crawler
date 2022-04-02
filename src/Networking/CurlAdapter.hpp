//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Networking/NetworkingProvider.hpp"

#include <string>
BEGIN_QTC_NAMESPACE

/**
 * @brief RAII Curl wrapper which allows to get contents of web page
 * @see NetworkingProvider
 * @warning To escure thread safety init global curl
 */
class CurlAdapter : public NetworkingProvider {

public:
    explicit CurlAdapter();
    ~CurlAdapter() override;
    Response Get(std::string const &url) override;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

class CurlAdapterFactory : public NetworkingProviderFactory {
public:
    using concrete_created_type = CurlAdapter;

    ~CurlAdapterFactory() override = default;
    created_type_p Create() const {
        return std::make_unique<concrete_created_type>();
    }
};

END_QTC_NAMESPACE