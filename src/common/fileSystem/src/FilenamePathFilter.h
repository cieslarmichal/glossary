#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace common::fileSystem
{
namespace fs = std::filesystem;
using FilePaths = std::vector<std::string>;

class FilenamePathFilter
{
public:
    FilePaths filterFilenames(const FilePaths&) const;

private:
    std::optional<std::string> getFilename(const fs::path&) const;
    bool isFile(const fs::path&) const;
};
}