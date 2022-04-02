//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Common/Namespace.h"
#include "qt_crawler/Configuration.hpp"

BEGIN_QTC_NAMESPACE

class ConfigurationMock : public Configuration {
public:
    ~ConfigurationMock() noexcept override = default;
    ConfigurationMock() {
        ON_CALL(*this, GetValue(testing::_)).WillByDefault(testing::Return(std::nullopt));
    }
    MOCK_METHOD(bool, HasKey, (std::string_view const), (const, noexcept, override));
    MOCK_METHOD((std::optional<std::string>), GetValue, (std::string_view const), (const, noexcept, override));
    MOCK_METHOD(std::string, Help, (), (const, noexcept, override));
};

END_QTC_NAMESPACE
