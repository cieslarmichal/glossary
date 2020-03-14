#pragma once

#include <experimental/filesystem>
#include <string>
#include <vector>

namespace utils
{
namespace fs = std::experimental::filesystem;
using FilePaths = std::vector<std::string>;

class FileExtensionsFilter
{
public:
    FilePaths filterByExtensions(const FilePaths&, const std::vector<std::string>& extensions) const;

private:
    bool containsAnyOfExtensions(const fs::path&, const std::vector<std::string>& fileExtensions) const;
};
}