#include "StringHelper.h"

#include "boost/algorithm/string.hpp"

namespace common::collection
{
std::string join(const std::vector<std::string>& contentWithLines, const std::string& joinWith)
{
    return boost::algorithm::join(contentWithLines, joinWith);
}

std::vector<std::string> split(const std::string& content, const std::string& splitBy)
{
    std::vector<std::string> contentWithLines;
    boost::split(contentWithLines, content, boost::is_any_of(splitBy));
    return contentWithLines;
}

std::string cutOffFromString(const std::string& line, size_t startIndexToCut, size_t endIndexToCut)
{
    const auto sizeOfLine = line.size();
    const auto head = line.substr(0, startIndexToCut);
    const auto tail = line.substr(endIndexToCut + 1, sizeOfLine - endIndexToCut + 1);
    return head + tail;
}

std::vector<std::string> getNonEmptyLines(const std::vector<std::string>& lines)
{
    std::vector<std::string> nonEmptyLines;
    for (const auto& line : lines)
    {
        if (not line.empty())
        {
            nonEmptyLines.push_back(line);
        }
    }
    return nonEmptyLines;
}

void removeEmptyLines(std::vector<std::string>& lines)
{
    lines.erase(std::remove_if(lines.begin(), lines.end(), [](std::string& line) { return line.empty(); }),
                lines.end());
}

void trim(std::vector<std::string>& lines)
{
    for (auto& line : lines)
    {
        trim(line);
    }
}

void removeDuplicates(std::vector<std::string>& lines)
{
    sort(lines.begin(), lines.end());
    lines.erase(unique(lines.begin(), lines.end()), lines.end());
}

void cutOffString(std::string& line, size_t startIndexToCut, size_t endIndexToCut)
{
    line = cutOffFromString(line, startIndexToCut, endIndexToCut);
}

std::string substring(const std::string& line, size_t startIndex, size_t endIndex)
{
    return line.substr(startIndex, endIndex - startIndex);
}

std::string getLowerCases(const std::string& input)
{
    return boost::algorithm::to_lower_copy(input);
}

void trim(std::string& line)
{
    boost::algorithm::trim(line);
}

}
