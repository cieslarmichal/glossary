#pragma once

#include <string>
#include <vector>

namespace utils
{
using ListOfFiles = std::vector<std::string>;

class FileExtensionsFilter
{
public:
    ListOfFiles filter(const ListOfFiles&, const std::vector<std::string>&) const;

private:
    bool isAnyOfExtensions(const std::string&, const std::vector<std::string>& fileExtensions) const;
};
}