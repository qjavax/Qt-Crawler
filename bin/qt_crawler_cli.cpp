//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#include <iostream>

#include "qt_crawler/Configuration.hpp"
#include "qt_crawler/ConfigurationKeys.hpp"
#include "qt_crawler/QtCrawlerApp.hpp"

int main(int argc, char *argv[]) {

    auto config = ConfigurationFactory().Create(argc, argv);

    if (config->HasKey(ConfigurationKeys::Key::help)) {
        std::cout << config->Help() << '\n';
        return 0;
    }
    QtCrawlerApp app(std::move(config));
    auto res = app.Run();
    if(!res) {
        std::cout << res.what() << '\n';
    }
    return res ? 0 : -1;
}
