#pragma once

#include <string>
#include <vector>

class HtmlParser
{
public:
    virtual ~HtmlParser() = default;

    virtual std::vector<std::string> parse(const std::string&) const = 0;
};
