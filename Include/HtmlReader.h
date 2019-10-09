#pragma once

#include <string>

class HtmlReader
{
public:
    virtual ~HtmlReader() = default;

    virtual std::string read(const std::string &) const = 0;
};
