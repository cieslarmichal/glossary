#include "HtmlTagsDeleter.h"

#include <algorithm>

#include "boost/algorithm/string.hpp"

#include "StringHelper.h"

namespace utils
{
namespace
{
bool containsHtmlOpenTagWithEndTag(const std::string&);
const std::string openHtmlTag{"<"};
const std::string endHtmlTag{">"};
}

std::vector<std::string> HtmlTagsDeleter::deleteTags(const std::vector<std::string>& htmlContent) const
{
    auto contentWithoutTags{htmlContent};
    clear(contentWithoutTags);
    return contentWithoutTags;
}

void HtmlTagsDeleter::clear(std::vector<std::string>& htmlLines) const
{
    for (auto& line : htmlLines)
    {
        removeHtmlTags(line);
    }
    trimEmptySpaces(htmlLines);
}

void HtmlTagsDeleter::removeHtmlTags(std::string& content) const
{
    while (containsHtmlOpenTagWithEndTag(content))
    {
        auto startTagPosition = content.find(openHtmlTag);
        auto endTagPos = content.find(endHtmlTag, startTagPosition);

        if (endTagPos != std::string::npos)
        {
            utils::cutOffString(content, startTagPosition, endTagPos);
        }
    }
}

void HtmlTagsDeleter::trimEmptySpaces(std::vector<std::string>& htmlLines) const
{
    htmlLines.erase(
        std::remove_if(htmlLines.begin(), htmlLines.end(), [](std::string& line) { return line.empty(); }),
        htmlLines.end());

    for (auto& line : htmlLines)
    {
        boost::algorithm::trim(line);
    }
}

namespace
{
bool containsHtmlOpenTagWithEndTag(const std::string& content)
{
    return ((content.find(openHtmlTag) != std::string::npos) &&
            (content.find(endHtmlTag) != std::string::npos));
}
}
}