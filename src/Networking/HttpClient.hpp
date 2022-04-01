//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Networking/Client.hpp"

#include <memory>

BEGIN_QTC_NAMESPACE

class HttpClient : public Client {
  public:
    explicit HttpClient(std::string const &host);
    ~HttpClient() override;

  private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};


END_QTC_NAMESPACE