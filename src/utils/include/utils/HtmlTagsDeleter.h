#pragma once

#include <string>
#include <vector>
#include "UtilsApi.h"

namespace utils
{
class HtmlTagsDeleter
{
public:
    UTILS_API std::vector<std::string> deleteTags(const std::vector<std::string>&) const;

private:
    void clear(std::vector<std::string>&) const;
    void removeHtmlTags(std::string&) const;
    void removeHtmlEntities(std::string&) const;
    void trimEmptySpaces(std::vector<std::string>&) const;
};
}