//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#include "Common/Namespace.h"
#include "Networking/CurlAdapter.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {
using namespace ::testing;
USING_QTC_NAMESPACE
} // namespace

class CurlAdapterFixture : public Test {
public:
    void SetUp() override {
        _curlAdapterFactory = std::make_shared<CurlAdapterFactory>();
    }

    std::shared_ptr<HtmlProvider> CreateCurlAdapter() {
        return _curlAdapterFactory->Create();
    }

private:
    std::shared_ptr<CurlAdapterFactory> _curlAdapterFactory;
};

TEST_F(CurlAdapterFixture, GIVEN_url_is_absolute_WHEN_NormalizeUrl_is_called_THEN_it_returns_same_url) {
    const std::string rootUrl = "https://sometestandnonexistingdomainname.com/";
    const std::string plainHtmlUrl = "https://sometestandnonexistingdomainname.com/somehtml.html";
    const std::string dirUrl = "https://sometestandnonexistingdomainname.com/subdir/";
    auto curlAdapter = this->CreateCurlAdapter();

    EXPECT_THAT(plainHtmlUrl, StrEq(*(curlAdapter->NormalizeUrl(rootUrl, plainHtmlUrl))));
    EXPECT_THAT(dirUrl, StrEq(*(curlAdapter->NormalizeUrl(rootUrl, dirUrl))));
}

TEST_F(CurlAdapterFixture, GIVEN_url_is_anachor_WHEN_NormalizeUrl_is_called_THEN_it_returns_nullopt) {
    const std::string rootUrl = "https://sometestandnonexistingdomainname.com/";
    const std::string anachor = "#something";
    auto curlAdapter = this->CreateCurlAdapter();

    EXPECT_TRUE(std::nullopt == curlAdapter->NormalizeUrl(rootUrl, anachor));
}

TEST_F(CurlAdapterFixture, GIVEN_url_is_relative_WHEN_NormalizeUrl_is_called_THEN_it_returns_merged_url) {
    const std::string rootUrl = "https://sometestandnonexistingdomainname.com/";
    const std::string relative = "something.html";
    auto curlAdapter = this->CreateCurlAdapter();

    EXPECT_THAT(rootUrl + relative, StrEq(*(curlAdapter->NormalizeUrl(rootUrl, relative))));
}

TEST_F(CurlAdapterFixture,
       GIVEN_url_is_relative_AND_root_is_plain_html_WHEN_NormalizeUrl_is_called_THEN_it_returns_merged_url) {
    const std::string rootUrl = "https://sometestandnonexistingdomainname.com/somehtml.html";
    const std::string relative = "something.html";
    auto curlAdapter = this->CreateCurlAdapter();

    EXPECT_THAT("https://sometestandnonexistingdomainname.com/something.html",
                StrEq(*(curlAdapter->NormalizeUrl(rootUrl, relative))));
}

TEST_F(CurlAdapterFixture,
       GIVEN_url_has_non_specified_protocol_WHEN_NormalizeUrl_is_called_THEN_it_returns_merged_url) {
    const std::string rootUrl = "https://sometestandnonexistingdomainname.com/somehtml.html";
    const std::string relative = "//sometestandnonexistingdomainname.com/subdir/";
    auto curlAdapter = this->CreateCurlAdapter();

    EXPECT_THAT("https://sometestandnonexistingdomainname.com/subdir/",
                StrEq(*(curlAdapter->NormalizeUrl(rootUrl, relative))));
}