//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Networking/NetworkingProvider.hpp"

#include <string>
BEGIN_QTC_NAMESPACE

class CurlAdapter : public NetworkingProvider {

  public:
    explicit CurlAdapter(std::string const &url);
    ~CurlAdapter() override;
    std::string Get(std::string const &url) const override;

  private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

class CurlAdapterFactory {};

END_QTC_NAMESPACE