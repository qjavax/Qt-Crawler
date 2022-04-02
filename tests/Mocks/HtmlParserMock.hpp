//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Parser/HtmlParser.hpp"

BEGIN_QTC_NAMESPACE

class HtmlParserMock : public HtmlParser {
public:
    virtual ~HtmlParserMock() = default;
    MOCK_METHOD(Result, Parse, (std::string const &), (override));
    MOCK_METHOD(std::vector<std::string>, GetAllLinks, (), (override));
};


END_QTC_NAMESPACE