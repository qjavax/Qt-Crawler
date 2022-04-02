//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#include "Mocks/HtmlParserMock.hpp"
#include "Mocks/HtmlProviderMock.hpp"
#include "Networking/HttpClient.hpp"
#include "gtest/gtest.h"

namespace {
using namespace ::testing;
USING_QTC_NAMESPACE
} // namespace

class HttpClientFixture : public Test {
public:
    const std::string fakeUrl = "https://sometestandnonexistingdomainname.com/";
    void SetUp() override {
        _htmlProviderFactory = std::make_shared<NiceMock<HtmlProviderFactoryMock>>();
        _htmlParser = std::make_shared<NiceMock<HtmlParserMock>>();
        _httpClientFactory = std::make_unique<HttpClientFactory>(_htmlProviderFactory, _htmlParser);
    }
    std::shared_ptr<Client> CreateHttpClient() {
        return _httpClientFactory->Create(fakeUrl);
    }

protected:
    std::unique_ptr<HttpClientFactory> _httpClientFactory;
    std::shared_ptr<NiceMock<HtmlParserMock>> _htmlParser;
    std::shared_ptr<NiceMock<HtmlProviderFactoryMock>> _htmlProviderFactory;
};

TEST_F(HttpClientFixture, HelloWorld) {
    EXPECT_TRUE(true);
}