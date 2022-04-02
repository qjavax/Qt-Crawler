//
// Created by qjava on 01.04.22
// Copyright (c) 2022 All rights reserved.
//
#include <iostream>
#include <string>

#include "qt_crawler/Configuration.hpp"
#include "qt_crawler/ConfigurationKeys.hpp"
#include "qt_crawler/QtCrawlerApp.hpp"

int main(int argc, char *argv[]) {

    Configuration config(argc, argv);

    if (config.HasKey(ConfigurationKeys::Key::help)) {
        std::cout << config.Help() << '\n';
        return 0;
    }
    QtCrawlerApp app(std::move(config));
    int res = app.Run();
    return res;
}
