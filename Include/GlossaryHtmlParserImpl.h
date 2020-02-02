#pragma once

#include <memory>

#include "GlossaryHtmlParser.h"
#include "HtmlTagsDeleter.h"

class GlossaryHtmlParserImpl : public GlossaryHtmlParser
{
public:
    GlossaryHtmlParserImpl();

    std::vector<std::string> parse(const std::string&) const override;

private:
    std::vector<std::string> selectGlossaryLines(const std::string&) const;

    std::unique_ptr<HtmlTagsDeleter> htmlTagsDeleter;
};
