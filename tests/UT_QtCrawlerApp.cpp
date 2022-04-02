//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Common/Namespace.h"
#include "Mocks/ConfigurationMock.hpp"
#include "qt_crawler/ConfigurationKeys.hpp"
#include "qt_crawler/QtCrawlerApp.hpp"

namespace {
using namespace ::testing;
USING_QTC_NAMESPACE
} // namespace

class QtCrawlerAppFixture : public Test {

public:
    void SetUp() override {}

    std::unique_ptr<NiceMock<ConfigurationMock>> CreateConfiguration() {
        return std::make_unique<NiceMock<ConfigurationMock>>();
    }
    std::shared_ptr<QtCrawlerApp> CreateApp(std::unique_ptr<NiceMock<ConfigurationMock>> config) {
        return std::make_shared<QtCrawlerApp>(std::move(config));
    }

protected:
};

TEST_F(QtCrawlerAppFixture, GIVEN_no_args_provided_WHEN_App_is_started_THEN_it_returns_error) {
    auto config = CreateConfiguration();
    EXPECT_CALL(*config, GetValue(StrEq(ConfigurationKeys::Key::url))).Times(1);
    // TODO: All required argument should be checked at once
    // EXPECT_CALL(*config, GetValue(StrEq(ConfigurationKeys::Key::outDir))).Times(1);

    auto app = this->CreateApp(std::move(config));
    auto result = app->Run();
    EXPECT_FALSE(result);
    EXPECT_THAT(result.what(), StartsWith("Missing required cmd argument"));
}

TEST_F(QtCrawlerAppFixture, GIVEN_required_args_provided_WHEN_App_is_started_THEN_it_should_not_fail) {
    auto config = CreateConfiguration();
    EXPECT_CALL(*config, GetValue(StrEq(ConfigurationKeys::Key::url)))
        .WillOnce(Return(std::optional<std::string>("https://test.io/")));
    EXPECT_CALL(*config, GetValue(StrEq(ConfigurationKeys::Key::outDir)))
        .WillOnce(Return(std::optional<std::string>("./testsTmpDir/")));

    auto app = this->CreateApp(std::move(config));
    auto result = app->Run();
    EXPECT_TRUE(result);
}
