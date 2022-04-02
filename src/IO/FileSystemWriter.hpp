//
// Created by qjava on 02.04.22
// Copyright (c) 2022 All rights reserved.
//
#pragma once
#include "Common/Namespace.h"
#include "Common/Types.h"
#include "IO/Writer.hpp"

BEGIN_QTC_NAMESPACE

class FileSystemWriter : public Writer<std::string> {
public:
    explicit FileSystemWriter(std::string const &rootDir);
    ~FileSystemWriter() override;
    Result Write(std::string const &data, std::string const &filename) override;

private:
    std::string _rootDir;
};

class FileSystemWriterFactory {
public:
    using created_type = Writer<std::string>;
    using created_type_p = std::unique_ptr<created_type>;
    using concrete_created_type = FileSystemWriter;

    ~FileSystemWriterFactory() = default;
    created_type_p Create(std::string const &rootDir) const {
        return std::make_unique<concrete_created_type>(std::move(rootDir));
    }
};
END_QTC_NAMESPACE