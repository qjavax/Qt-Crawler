//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Common/Namespace.h"
#include "Networking/Client.hpp"

BEGIN_QTC_NAMESPACE

class ClientMock : public Client {
public:
    ~ClientMock() override = default;
    MOCK_METHOD(Result, VisitAndSaveAllSubpages(std::string const &), (override));
};

END_QTC_NAMESPACE
