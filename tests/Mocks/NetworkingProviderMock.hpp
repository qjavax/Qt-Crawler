//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "gtest/gtest.h"

#include "Networking/NetworkingProvider.hpp"

BEGIN_QTC_NAMESPACE

class NetworkingProviderMock {

  public:
    virtual ~NetworkingProviderMock() = default;
    MOCK_METHOD(std::string, Get, (std::string const&, (const, override));
};


END_QTC_NAMESPACE