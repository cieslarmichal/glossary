#pragma once

#include <string>
#include <vector>

class GlossaryHtmlParser
{
public:
    virtual ~GlossaryHtmlParser() = default;

    virtual std::vector<std::string> parse(const std::string&) const = 0;
};
