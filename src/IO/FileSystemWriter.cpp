#include "FileSystemWriter.hpp"

#include <fstream>
#include <fmt/core.h>

namespace {
USING_QTC_NAMESPACE

} // namespace


FileSystemWriter::FileSystemWriter(std::string const &rootDir)
    : _rootDir(std::move(rootDir)) {}

FileSystemWriter::~FileSystemWriter() = default;

Result FileSystemWriter::Write(std::string const &data, std::string const &filename) {
    auto fullPath = _rootDir + '/' + filename;
    std::ofstream outStream;
    outStream.open(fullPath, std::ofstream::out | std::ofstream::trunc);
    
    if (!outStream.is_open()) {
        return Result(Result::Success::No, "Cannot open file for writing: " + fullPath);
    }
    fmt::print("Writting stream to file {}\n", fullPath);
    outStream << data;
    outStream.close();
    return (Result::Success::Yes);
}
