#pragma once

#include <string>
#include <vector>
#include "UtilsApi.h"

namespace utils
{
const std::string endOfLine{"\n"};

UTILS_API std::string join(const std::vector<std::string>& contentWithLines, const std::string& joinWith = endOfLine);
UTILS_API std::vector<std::string> split(const std::string& content, const std::string& splitBy = endOfLine);
UTILS_API std::vector<std::string> getNonEmptyLines(const std::vector<std::string>&);
UTILS_API void removeEmptyLines(std::vector<std::string>&);
UTILS_API void trim(std::vector<std::string>&);
UTILS_API void removeDuplicates(std::vector<std::string>&);
UTILS_API std::string cutOffFromString(const std::string& line, size_t startIndexToCut, size_t endIndexToCut);
UTILS_API void cutOffString(std::string& line, size_t startIndexToCut, size_t endIndexToCut);
UTILS_API std::string substring(const std::string& line, size_t startIndex, size_t endIndex);
UTILS_API std::string getLowerCases(const std::string&);
UTILS_API void trim(std::string&);
}
