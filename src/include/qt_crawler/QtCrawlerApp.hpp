//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Types.h"
#include "qt_crawler/Configuration.hpp"
#include <memory>

class QtCrawlerApp {
public:
    explicit QtCrawlerApp(std::unique_ptr<Configuration> config) noexcept;
    ~QtCrawlerApp() noexcept;
    Result Run() noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};