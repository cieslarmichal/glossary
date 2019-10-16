#pragma once

#include <string>
#include <vector>

namespace stringHelper
{

std::string getJoinedLines(const std::vector<std::string> &contentWithLines);
std::vector<std::string> getSplitLines(const std::string &content);
std::string cutOffFromString(const std::string &line, size_t startIndexToCut, size_t endIndexToCut);
void cutOffString(std::string &line, size_t startIndexToCut, size_t endIndexToCut);
std::string substring(const std::string &line, size_t startIndex, size_t endIndex);
std::string getCaseInsensitive(const std::string&);
}
