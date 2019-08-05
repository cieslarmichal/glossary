#pragma once

#include "HtmlParser.h"

class DefaultHtmlParser : public HtmlParser
{
public:
    std::vector<std::string> parse(const std::string &) const override;

protected:
    std::vector<std::string> splitLines(const std::string &) const;

private:
    void removeHtmlStrings(std::vector<std::string> &) const;
    void removeExtraLines(std::vector<std::string> &) const;
};