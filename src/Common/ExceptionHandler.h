//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include <iostream>

#define TRY try {

#define CATCH_STD                      \
    }                                  \
    catch (const std::exception &ex) { \
        std::cerr << "Exception catched: " << ex.what() << '\n';
#define CATCH_ALL                                   \
    }                                               \
    catch (...) {                                   \
        std::cerr << "Unknown exception catched\n"; \
    }
