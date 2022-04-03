//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "IO/Writer.hpp"
#include "Networking/Client.hpp"
#include "Networking/HtmlProvider.hpp"
#include "Parser/HtmlParser.hpp"
#include <memory>

BEGIN_QTC_NAMESPACE

/**
 * @brief High-level implementation of the Client that allows you to search url subpages and perform Write on them
 * @see Client
 */
class HttpClient : public Client {
public:
    explicit HttpClient(std::shared_ptr<HtmlProviderFactory> htmlProviderFactory,
                        std::shared_ptr<HtmlParser> htmlParser, std::string const &url);
    ~HttpClient() override;
    Result VisitAndSaveAllSubpages(std::shared_ptr<Writer<std::string>> writer) override;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

class HttpClientFactory {
public:
    using created_type = Client;
    using created_type_p = std::unique_ptr<created_type>;
    using concrete_created_type = HttpClient;

    explicit HttpClientFactory(std::shared_ptr<HtmlProviderFactory> htmlProviderFactory,
                               std::shared_ptr<HtmlParser> htmlParser)
        : _htmlProviderFactory(std::move(htmlProviderFactory))
        , _htmlParser(std::move(htmlParser)) {}
    ~HttpClientFactory() = default;

    created_type_p Create(std::string const &url) const {
        return std::make_unique<concrete_created_type>(_htmlProviderFactory, _htmlParser, std::move(url));
    }

private:
    std::shared_ptr<HtmlProviderFactory> _htmlProviderFactory;
    std::shared_ptr<HtmlParser> _htmlParser;
};

END_QTC_NAMESPACE