#include "DefaultHtmlParser.h"

#include <algorithm>

#include "StringHelper.h"

namespace
{
void removeHtmlTags(std::string&);

bool containsOpenHtmlTag(const std::string&);

bool containsCloseHtmlTag(const std::string&);

size_t findOpenHtmlTag(const std::string&);

size_t findCloseHtmlTag(const std::string&);

const std::string openHtmlTag{"<"};
const std::string closeHtmlTag{">"};
}

std::vector<std::string>
DefaultHtmlParser::parse(const std::string& htmlContent) const
{
    auto parsedContent = stringHelper::getSplitLines(htmlContent);

    removeHtmlStrings(parsedContent);

    removeExtraLines(parsedContent);

    return parsedContent;
}

void DefaultHtmlParser::removeHtmlStrings(
    std::vector<std::string>& htmlContent) const
{
    for (auto& line : htmlContent)
    {
        removeHtmlTags(line);
    }
}

void DefaultHtmlParser::removeExtraLines(
    std::vector<std::string>& htmlContent) const
{
    htmlContent.erase(
        std::remove_if(htmlContent.begin(), htmlContent.end(),
                       [](std::string& line) { return line.empty(); }),
        htmlContent.end());
}

namespace
{

void removeHtmlTags(std::string& line)
{
    while (containsOpenHtmlTag(line) && containsCloseHtmlTag(line))
    {
        auto openSignPosition = findOpenHtmlTag(line);
        auto closeSignPosition = findCloseHtmlTag(line);
        line = stringHelper::cutOffFromString(line, openSignPosition,
                                              closeSignPosition);
    }
}

bool containsOpenHtmlTag(const std::string& line)
{
    return (line.find(openHtmlTag) != std::string::npos);
}

bool containsCloseHtmlTag(const std::string& line)
{
    return (line.find(closeHtmlTag) != std::string::npos);
}

size_t findOpenHtmlTag(const std::string& line)
{
    return line.find(openHtmlTag);
}

size_t findCloseHtmlTag(const std::string& line)
{
    return line.find(closeHtmlTag);
}

}