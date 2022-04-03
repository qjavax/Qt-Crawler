//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#include "Mocks/HtmlParserMock.hpp"
#include "Mocks/HtmlProviderMock.hpp"
#include "Mocks/WriterMock.hpp"
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
        _writer = std::make_shared<NiceMock<WriterMock<std::string>>>();
    }
    std::shared_ptr<Client> CreateHttpClient() {
        return _httpClientFactory->Create(fakeUrl);
    }
    std::unique_ptr<NiceMock<HtmlProviderMock>> CreateHtmlProviderMock() {
        return std::make_unique<NiceMock<HtmlProviderMock>>();
    }

protected:
    std::unique_ptr<HttpClientFactory> _httpClientFactory;
    std::shared_ptr<NiceMock<HtmlParserMock>> _htmlParser;
    std::shared_ptr<NiceMock<HtmlProviderFactoryMock>> _htmlProviderFactory;
    std::shared_ptr<NiceMock<WriterMock<std::string>>> _writer;
};

TEST_F(HttpClientFixture,
       GIVEN_root_url_cannot_be_normalized_WHEN_VisitAndSaveAllSubpages_is_called_THEN_it_returns_error) {
    auto htmlProvider = this->CreateHtmlProviderMock();
    EXPECT_CALL(*htmlProvider, NormalizeUrl(_, _)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*_htmlProviderFactory, Create()).WillOnce(Return(ByMove(std::move(htmlProvider))));

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_FALSE(result);
}

TEST_F(HttpClientFixture,
       GIVEN_root_url_cannot_be_validated_WHEN_VisitAndSaveAllSubpages_is_called_THEN_it_returns_error) {
    auto htmlProvider = this->CreateHtmlProviderMock();
    EXPECT_CALL(*htmlProvider, ValidateUrl(_)).WillOnce(Return(HtmlProvider::Response(Result(Result::Success::No))));
    EXPECT_CALL(*_htmlProviderFactory, Create()).WillOnce(Return(ByMove(std::move(htmlProvider))));

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_FALSE(result);
}

TEST_F(HttpClientFixture,
       GIVEN_root_html_cannot_be_writen_WHEN_VisitAndSaveAllSubpages_is_called_THEN_it_returns_error) {
    auto htmlProvider = this->CreateHtmlProviderMock();
    EXPECT_CALL(*htmlProvider, Get(_))
        .WillOnce(Return(HtmlProvider::Response(Result(Result::Success::Yes), "fakeData")));

    EXPECT_CALL(*_htmlProviderFactory, Create()).WillOnce(Return(ByMove(std::move(htmlProvider))));

    EXPECT_CALL(*_writer, Write(_, _)).WillOnce(Return(Result(Result::Success::No)));

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_FALSE(result);
}

TEST_F(HttpClientFixture,
       GIVEN_root_html_cannot_be_parsed_WHEN_VisitAndSaveAllSubpages_is_called_THEN_it_returns_error) {
    auto htmlProvider = this->CreateHtmlProviderMock();
    EXPECT_CALL(*htmlProvider, Get(_))
        .WillOnce(Return(HtmlProvider::Response(Result(Result::Success::Yes), "fakeData")));

    EXPECT_CALL(*_htmlProviderFactory, Create()).WillOnce(Return(ByMove(std::move(htmlProvider))));

    EXPECT_CALL(*_htmlParser, Parse(_)).WillOnce(Return(Result(Result::Success::No)));

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_FALSE(result);
}

TEST_F(HttpClientFixture,
       GIVEN_no_error_is_returned_on_root_WHEN_VisitAndSaveAllSubpages_is_called_THEN_root_is_writen_and_parsed) {
    auto htmlProvider = this->CreateHtmlProviderMock();
    EXPECT_CALL(*htmlProvider, Get(_))
        .WillOnce(Return(HtmlProvider::Response(Result(Result::Success::Yes), "fakeData")));

    EXPECT_CALL(*_htmlParser, Parse(_)).Times(1);
    EXPECT_CALL(*_writer, Write(_, _)).Times(1);
    EXPECT_CALL(*_htmlProviderFactory, Create()).WillOnce(Return(ByMove(std::move(htmlProvider))));

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_TRUE(result);
}

TEST_F(HttpClientFixture,
       GIVEN_root_html_has_no_subpages_WHEN_VisitAndSaveAllSubpages_is_called_THEN_only_root_is_writen_and_parsed) {
    auto htmlProvider = this->CreateHtmlProviderMock();
    EXPECT_CALL(*htmlProvider, Get(_))
        .WillOnce(Return(HtmlProvider::Response(Result(Result::Success::Yes), "fakeData")));

    EXPECT_CALL(*_htmlParser, GetAllLinks()).WillOnce(Return(std::vector<std::string>()));
    EXPECT_CALL(*_writer, Write(_, _)).Times(1);
    EXPECT_CALL(*_htmlParser, Parse(_)).Times(1);

    EXPECT_CALL(*_htmlProviderFactory, Create()).WillOnce(Return(ByMove(std::move(htmlProvider))));

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_TRUE(result);
}

TEST_F(
    HttpClientFixture,
    GIVEN_root_html_has_subpages_AND_all_are_valid_WHEN_VisitAndSaveAllSubpages_is_called_THEN_all_pages_are_writen) {
    const std::vector<std::string> subpages{{"url", "url", "url"}};

    EXPECT_CALL(*_htmlParser, GetAllLinks()).WillOnce(Return(subpages));
    EXPECT_CALL(*_writer, Write(_, _)).Times(1 + subpages.size());
    EXPECT_CALL(*_htmlParser, Parse(_)).Times(1);

    EXPECT_CALL(*_htmlProviderFactory, Create()).Times(1 + subpages.size()).WillRepeatedly(DoDefault());

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_TRUE(result);
}

TEST_F(
    HttpClientFixture,
    GIVEN_root_html_has_subpages_AND_some_are_invalid_WHEN_VisitAndSaveAllSubpages_is_called_THEN_valid_pages_are_writen) {
    const std::vector<std::string> subpages{{"url", "url", "url"}};
    auto htmlProvider = this->CreateHtmlProviderMock();
    EXPECT_CALL(*htmlProvider, ValidateUrl(_)).WillOnce(Return(HtmlProvider::Response(Result(Result::Success::No))));

    EXPECT_CALL(*_htmlParser, GetAllLinks()).WillOnce(Return(subpages));
    EXPECT_CALL(*_writer, Write(_, _)).Times(3); // 1 root page + 2 valid subpages
    EXPECT_CALL(*_htmlParser, Parse(_)).Times(1);

    EXPECT_CALL(*_htmlProviderFactory, Create())
        .WillOnce(DoDefault())
        .WillOnce(DoDefault())
        .WillOnce(Return(ByMove(std::move(htmlProvider)))) // provide Not Validating HTML provider on 3rd call
        .WillOnce(DoDefault());

    auto client = this->CreateHttpClient();
    auto result = client->VisitAndSaveAllSubpages(_writer);
    EXPECT_TRUE(result);
}