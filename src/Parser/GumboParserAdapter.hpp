//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"
#include "Parser/HtmlParser.hpp"

BEGIN_QTC_NAMESPACE
/**
 * @brief HtmlParser implemented with gumbo-parser behaviour
 * @see HtmlParser
 */
class GumboParserAdapter : public HtmlParser {
public:
    explicit GumboParserAdapter();
    ~GumboParserAdapter() override;
    Result Parse(std::string const &data) override;
    std::vector<std::string> GetAllLinks() override;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

class GumboParserAdapterFactory {
public:
    using created_type = HtmlParser;
    using created_type_p = std::unique_ptr<created_type>;
    using concrete_created_type = GumboParserAdapter;

    created_type_p Create() const {
        return std::make_unique<concrete_created_type>();
    }
};

END_QTC_NAMESPACE