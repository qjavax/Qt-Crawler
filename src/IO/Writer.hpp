//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"

BEGIN_QTC_NAMESPACE

template <typename Data>
class Writer {
public:
    virtual ~Writer() = default;
    virtual Result Write(Data const &data, std::string const &dest) = 0;
};


END_QTC_NAMESPACE