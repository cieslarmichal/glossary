#pragma once

#include <string>
#include <vector>

namespace glossary::wordDescriptionDownloader
{
class LinesSelector
{
public:
    virtual ~LinesSelector() = default;

    virtual std::vector<std::string> selectLines(const std::string&) const = 0;
};
}