#include "DefaultHtmlParser.h"

#include "boost/algorithm/string.hpp"
#include <iostream>
#include <algorithm>

namespace
{
void removeHtmlTags(std::string &);

bool containsOpenHtmlTag(const std::string &);

bool containsCloseHtmlTag(const std::string &);

size_t findOpenHtmlTag(const std::string &);

size_t findCloseHtmlTag(const std::string &);

std::string cutOffFromString(const std::string &, size_t, size_t);

const std::string openHtmlTag{"<"};
const std::string closeHtmlTag{">"};
const std::string endOfLine{"\n"};
}

std::vector<std::string> DefaultHtmlParser::parse(const std::string &htmlContent) const
{
    auto parsedContent = splitLines(htmlContent);

    removeHtmlStrings(parsedContent);

    removeExtraLines(parsedContent);

    return parsedContent;
}

std::vector<std::string> DefaultHtmlParser::splitLines(const std::string &htmlContent) const
{
    std::vector<std::string> htmlContentLines;
    boost::split(htmlContentLines, htmlContent, boost::is_any_of(endOfLine));
    return htmlContentLines;
}

void DefaultHtmlParser::removeHtmlStrings(std::vector<std::string> &htmlContent) const
{
    for (auto &line : htmlContent)
    {
        removeHtmlTags(line);
    }
}

void DefaultHtmlParser::removeExtraLines(std::vector<std::string> &htmlContent) const
{
    htmlContent.erase(std::remove_if(htmlContent.begin(), htmlContent.end(),
            [](std::string &line) { return (line.size() == 0); }), htmlContent.end());
}

namespace
{

void removeHtmlTags(std::string &line)
{
    while (containsOpenHtmlTag(line) && containsCloseHtmlTag(line))
    {
        auto openSignPosition = findOpenHtmlTag(line);
        auto closeSignPosition = findCloseHtmlTag(line);
        line = cutOffFromString(line, openSignPosition, closeSignPosition);
    }
}

bool containsOpenHtmlTag(const std::string &line)
{
    return (line.find(openHtmlTag) != std::string::npos);
}

bool containsCloseHtmlTag(const std::string &line)
{
    return (line.find(closeHtmlTag) != std::string::npos);
}

size_t findOpenHtmlTag(const std::string &line)
{
    return line.find(openHtmlTag);
}

size_t findCloseHtmlTag(const std::string &line)
{
    return line.find(closeHtmlTag);
}

std::string cutOffFromString(const std::string &line, size_t startIndexToCut, size_t endIndexToCut)
{
    auto sizeOfLine = line.size();

    auto head = line.substr(0, startIndexToCut);
    auto tail = line.substr(endIndexToCut + 1, sizeOfLine - endIndexToCut);

    return head + tail;
}

}