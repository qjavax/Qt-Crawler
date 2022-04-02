//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"

#include <string>
#include <vector>

BEGIN_QTC_NAMESPACE

class HtmlParser {
  public:
    virtual ~HtmlParser() = default;
    virtual Result Parse(std::string const& data) = 0;
    virtual std::vector<std::string> GetAllLinks() = 0;
};


END_QTC_NAMESPACE