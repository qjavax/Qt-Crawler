//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Networking/NetworkingProvider.hpp"

BEGIN_QTC_NAMESPACE

class NetworkingProviderMock : public NetworkingProvider {
  public:
    virtual ~NetworkingProviderMock() = default;
    MOCK_METHOD(Response, Get, (std::string const&), (override));
};


END_QTC_NAMESPACE