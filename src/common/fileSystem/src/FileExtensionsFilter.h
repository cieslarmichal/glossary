#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace common::fileSystem
{
namespace fs = std::filesystem;
using FilePaths = std::vector<std::string>;

class FileExtensionsFilter
{
public:
    FilePaths filterByExtensions(const FilePaths&, const std::vector<std::string>& extensions) const;

private:
    bool containsAnyOfExtensions(const fs::path&, const std::vector<std::string>& fileExtensions) const;
};
}