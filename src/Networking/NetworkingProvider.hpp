//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"

#include <string>
BEGIN_QTC_NAMESPACE

class NetworkingProvider {

public:
    virtual ~NetworkingProvider() = default;
    virtual std::string Get(std::string const& url) const;
     
};


END_QTC_NAMESPACE