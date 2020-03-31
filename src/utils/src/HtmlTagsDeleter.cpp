#include "HtmlTagsDeleter.h"

#include "StringHelper.h"

namespace utils
{
namespace
{
bool containsHtmlStartingAndClosingTag(const std::string&);
bool containsHtmlEntityStartingAndClosingTag(const std::string&);
const std::string startingHtmlTag{"<"};
const std::string closingHtmlTag{">"};
const std::string startingEntityNameTag{"&"};
const std::string closingEntityNameTag{";"};
}

std::vector<std::string> HtmlTagsDeleter::deleteTags(const std::vector<std::string>& htmlContent) const
{
    auto content{htmlContent};
    clear(content);
    return content;
}

void HtmlTagsDeleter::clear(std::vector<std::string>& htmlLines) const
{
    for (auto& line : htmlLines)
    {
        removeHtmlTags(line);
        removeHtmlEntities(line);
    }
    trimEmptySpaces(htmlLines);
}

void HtmlTagsDeleter::removeHtmlTags(std::string& content) const
{
    while (containsHtmlStartingAndClosingTag(content))
    {
        auto startTagPosition = content.find(startingHtmlTag);
        auto endTagPos = content.find(closingHtmlTag, startTagPosition);

        if (endTagPos != std::string::npos)
        {
            utils::cutOffString(content, startTagPosition, endTagPos);
        }
    }
}

void HtmlTagsDeleter::removeHtmlEntities(std::string& content) const
{
    while (containsHtmlEntityStartingAndClosingTag(content))
    {
        auto startTagPosition = content.find(startingEntityNameTag);
        auto endTagPos = content.find(closingEntityNameTag, startTagPosition);

        if (endTagPos != std::string::npos)
        {
            utils::cutOffString(content, startTagPosition, endTagPos);
        }
    }
}

void HtmlTagsDeleter::trimEmptySpaces(std::vector<std::string>& htmlLines) const
{
    utils::removeEmptyLines(htmlLines);
    utils::trim(htmlLines);
}

namespace
{
bool containsHtmlStartingAndClosingTag(const std::string& content)
{
    return ((content.find(startingHtmlTag) != std::string::npos) &&
            (content.find(closingHtmlTag) != std::string::npos));
}

bool containsHtmlEntityStartingAndClosingTag(const std::string& content)
{
    return ((content.find(startingEntityNameTag) != std::string::npos) &&
            (content.find(closingEntityNameTag) != std::string::npos));
}

}
}