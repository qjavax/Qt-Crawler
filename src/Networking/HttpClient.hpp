//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Networking/Client.hpp"
#include "Networking/NetworkingProvider.hpp"
#include "Parser/HtmlParser.hpp"
#include <memory>

BEGIN_QTC_NAMESPACE

class HttpClient : public Client {
public:
    explicit HttpClient(std::shared_ptr<NetworkingProviderFactory> networkingProviderFactory,
                        std::shared_ptr<HtmlParser> htmlParser, std::string const &url);
    ~HttpClient() override;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

class HttpClientFactory {
public:
    using created_type = Client;
    using created_type_p = std::unique_ptr<created_type>;
    using concrete_created_type = HttpClient;

    explicit HttpClientFactory(std::shared_ptr<NetworkingProviderFactory> networkingProviderFactory,
                               std::shared_ptr<HtmlParser> htmlParser)
        : _networkingProviderFactory(std::move(networkingProviderFactory))
        , _htmlParser(std::move(htmlParser)) {}
    ~HttpClientFactory() = default;

    created_type_p Create(std::string const &url) const {
        return std::make_unique<concrete_created_type>(_networkingProviderFactory, _htmlParser, std::move(url));
    }

private:
    std::shared_ptr<NetworkingProviderFactory> _networkingProviderFactory;
    std::shared_ptr<HtmlParser> _htmlParser;
};

END_QTC_NAMESPACE