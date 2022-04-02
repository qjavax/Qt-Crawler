//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"

BEGIN_QTC_NAMESPACE

class Client {
public:
    virtual ~Client() = default;
    virtual Result VisitAndSaveAllSubpages(std::shared_ptr<Writer<std::string>>) = 0;
};


END_QTC_NAMESPACE