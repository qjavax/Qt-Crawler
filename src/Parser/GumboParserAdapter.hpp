//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"
#include "Parser/HtmlParser.hpp"

BEGIN_QTC_NAMESPACE

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


END_QTC_NAMESPACE