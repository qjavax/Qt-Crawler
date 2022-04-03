#include "FileSystemWriter.hpp"

#include "Common/ExceptionHandler.h"
#include <filesystem>
#include <fstream>
namespace {
USING_QTC_NAMESPACE

} // namespace


FileSystemWriter::FileSystemWriter(std::string const &rootDir)
    : _rootDir(std::move(rootDir)) {
    TRY if (!std::filesystem::exists(rootDir)) {
        std::filesystem::create_directory(rootDir);
    }
    CATCH_STD
    CATCH_ALL
}

FileSystemWriter::~FileSystemWriter() = default;

Result FileSystemWriter::Write(std::string const &data, std::string const &filename) {
    TRY auto fullPath = _rootDir + '/' + filename;
    std::ofstream outStream;
    outStream.open(fullPath, std::ofstream::out | std::ofstream::trunc);

    if (!outStream.is_open()) {
        return Result(Result::Success::No, "Cannot open file for writing: " + fullPath);
    }
    outStream << data;
    outStream.close();
    return Result(Result::Success::Yes);
    CATCH_STD
    CATCH_ALL
    return Result(Result::Success::No, "Exception catched while writting to file");
}
