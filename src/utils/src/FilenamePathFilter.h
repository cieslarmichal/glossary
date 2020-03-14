#pragma once

#include <string>
#include <vector>

#include <experimental/filesystem>
#include "boost/optional.hpp"

namespace utils
{
using ListOfFiles = std::vector<std::string>;

class FilenamePathFilter
{
public:
    ListOfFiles filter(const ListOfFiles&) const;

private:
    boost::optional<std::string> getFilename(const std::string&) const;
    bool isFile(const std::experimental::filesystem::path&) const;
};
}