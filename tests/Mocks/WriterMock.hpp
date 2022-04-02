//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"

BEGIN_QTC_NAMESPACE

template <typename Data>
class WriterMock {
public:
    virtual ~WriterMock() = default;

    MOCK_METHOD(Result, Write, (Data const &, std::string const &), (override));
};


END_QTC_NAMESPACE