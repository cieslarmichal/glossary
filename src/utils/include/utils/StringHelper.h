#pragma once

#include <string>
#include <vector>

namespace utils
{
const std::string endOfLine{"\n"};

std::string join(const std::vector<std::string>& contentWithLines, const std::string& joinWith = endOfLine);
std::vector<std::string> split(const std::string& content, const std::string& splitBy = endOfLine);
std::vector<std::string> getNonEmptyLines(const std::vector<std::string>&);
void removeEmptyLines(std::vector<std::string>&);
void trim(std::vector<std::string>&);
void removeDuplicates(std::vector<std::string>&);
std::string cutOffFromString(const std::string& line, size_t startIndexToCut, size_t endIndexToCut);
void cutOffString(std::string& line, size_t startIndexToCut, size_t endIndexToCut);
std::string substring(const std::string& line, size_t startIndex, size_t endIndex);
std::string getLowerCases(const std::string&);
void trim(std::string&);
}
