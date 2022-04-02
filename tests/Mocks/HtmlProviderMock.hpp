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
    MOCK_METHOD(Response, Get, (std::string const &), (override));
};


class HtmlProviderFactoryMock : public HtmlProviderFactory {
public:
    ~HtmlProviderFactoryMock() override = default;
    HtmlProviderFactoryMock() {
        ON_CALL(*this, Create())
            .WillByDefault(Return(ByMove(std::make_unique<testing::NiceMock<HtmlProviderMock>>())));
    }
    MOCK_METHOD(created_type_p, Create, (), (const, override));
};

END_QTC_NAMESPACE