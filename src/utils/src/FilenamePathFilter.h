#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <boost/optional.hpp>

namespace utils
{
namespace fs = std::filesystem;
using FilePaths = std::vector<std::string>;

class FilenamePathFilter
{
public:
    FilePaths filterFilenames(const FilePaths&) const;

private:
    boost::optional<std::string> getFilename(const fs::path&) const;
    bool isFile(const fs::path&) const;
};
}