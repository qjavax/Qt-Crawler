//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Common/Namespace.h"
#include "Networking/HtmlProvider.hpp"

BEGIN_QTC_NAMESPACE

class HtmlProviderMock : public HtmlProvider {
public:
    virtual ~HtmlProviderMock() = default;
    HtmlProviderMock() {
        ON_CALL(*this, Get(testing::_))
            .WillByDefault(testing::Return(HtmlProvider::Response(Result(Result::Success::Yes), "fakeData")));
        ON_CALL(*this, NormalizeUrl(testing::_, testing::_))
            .WillByDefault(testing::Invoke([](std::string const &rootUrl, std::string const &) { return rootUrl; }));
        ON_CALL(*this, ValidateUrl(testing::_)).WillByDefault(testing::Return(Response(Result(Result::Success::Yes))));
    }
    MOCK_METHOD(Response, Get, (std::string const &), (override));
    MOCK_METHOD(Response, ValidateUrl, (std::string const &), (override));
    MOCK_METHOD((std::optional<std::string>), NormalizeUrl, (std::string const &, std::string const &), (override));
};

class HtmlProviderFactoryMock : public HtmlProviderFactory {
public:
    ~HtmlProviderFactoryMock() override = default;
    HtmlProviderFactoryMock() {
        ON_CALL(*this, Create()).WillByDefault(testing::Invoke([]() {
            return std::make_unique<testing::NiceMock<HtmlProviderMock>>();
        }));
    }
    MOCK_METHOD(created_type_p, Create, (), (const, override));
};

END_QTC_NAMESPACE