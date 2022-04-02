//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "qt_crawler/Configuration.hpp"

#include <memory>

class QtCrawlerApp {
public:
    explicit QtCrawlerApp(Configuration &&config) noexcept;
    ~QtCrawlerApp() noexcept;
    int Run() noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};