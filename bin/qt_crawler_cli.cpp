//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#include <iostream>
#include <string>

#include <cxxopts.hpp>

#include "qt_crawler/QtCrawler.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    cxxopts::Options options("qt_crawler", "QT Documentation Crawler");
    options.add_options()("h,help", "Show help.", cxxopts::value<bool>()->default_value("false"));
    auto parsedOpts = options.parse(argc, argv);

    if (parsedOpts.count("help")) {
        std::cout << options.help() << '\n';
        return 0;
    }

    return 0;
}
