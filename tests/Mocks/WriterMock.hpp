//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IO/Writer.hpp"

BEGIN_QTC_NAMESPACE

template <typename Data>
class WriterMock : public Writer<Data> {
public:
    virtual ~WriterMock() = default;
    WriterMock() {
        ON_CALL(*this, Write(testing::_, testing::_)).WillByDefault(testing::Return(Result(Result::Success::Yes)));
    }
    MOCK_METHOD(Result, Write, (Data const &, std::string const &), (override));
};

END_QTC_NAMESPACE