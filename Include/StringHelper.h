#pragma once

#include <string>
#include <vector>

namespace stringHelper
{

std::string getJoinedLines(const std::vector<std::string> &contentWithLines);

std::vector<std::string> getSplitLines(const std::string &content);

std::string cutOffFromString(const std::string &line, size_t startIndexToCut, size_t endIndexToCut);

}
