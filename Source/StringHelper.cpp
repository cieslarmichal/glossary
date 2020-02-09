#include "StringHelper.h"

#include "boost/algorithm/string.hpp"

namespace
{
const std::string endOfLine{"\n"};

}

namespace stringHelper
{

std::string getJoinedLines(const std::vector<std::string>& contentWithLines)
{
    return boost::algorithm::join(contentWithLines, endOfLine);
}

std::vector<std::string> getSplitLines(const std::string& content)
{
    std::vector<std::string> contentWithLines;
    boost::split(contentWithLines, content, boost::is_any_of(endOfLine));
    return contentWithLines;
}

std::string cutOffFromString(const std::string& line, size_t startIndexToCut,
                             size_t endIndexToCut)
{
    const auto sizeOfLine = line.size();
    const auto head = line.substr(0, startIndexToCut);
    const auto tail = line.substr(endIndexToCut + 1, sizeOfLine - endIndexToCut + 1);
    return head + tail;
}

void cutOffString(std::string& line, size_t startIndexToCut,
                  size_t endIndexToCut)
{
    line = cutOffFromString(line, startIndexToCut, endIndexToCut);
}

std::string substring(const std::string& line, size_t startIndex,
                      size_t endIndex)
{
    return line.substr(startIndex, endIndex - startIndex);
}

std::string getLowerCases(const std::string& input)
{
    return boost::algorithm::to_lower_copy(input);
}

}
