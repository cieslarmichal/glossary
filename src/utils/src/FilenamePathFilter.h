#pragma once

#include <string>
#include <vector>

namespace utils
{
using ListOfFiles = std::vector<std::string>;

class FilenamePathFilter
{
public:
    ListOfFiles filter(const ListOfFiles&) const;

private:
    std::string getFilename(const std::string&) const;
};
}