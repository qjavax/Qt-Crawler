#include "FileSystemWriter.hpp"


namespace {
USING_QTC_NAMESPACE

} // namespace


FileSystemWriter::FileSystemWriter(std::string const &rootDir)
    : _rootDir(std::move(rootDir)) {}

FileSystemWriter::~FileSystemWriter() = default;

Result FileSystemWriter::Write(std::string const &data, std::string const &filename) {

    auto fullPath = _rootDir + "/" + filename;
}
