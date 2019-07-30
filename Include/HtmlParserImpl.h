#pragma once

#include "HtmlParser.h"

class HtmlParserImpl : public HtmlParser
{
public:
    std::vector<std::string> parse(const std::string &) const override;

private:
    std::vector<std::string> selectImportantLines(const std::string &) const;

    std::string removeHtmlTags(const std::string &) const;

};