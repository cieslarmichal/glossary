#pragma once

#include <string>
#include <vector>

namespace utils
{
class HtmlTagsDeleter
{
public:
    std::vector<std::string> deleteTags(const std::vector<std::string>&) const;

private:
    void clear(std::vector<std::string>&) const;
    void removeHtmlTags(std::string&) const;
    void trimEmptySpaces(std::vector<std::string>&) const;
};
}