#pragma once

#include <memory>

#include "LinesSelector.h"
#include "utils/HtmlTagsDeleter.h"

namespace glossary::wordDescriptionDownloader
{
class HtmlDescriptionLinesSelector : public LinesSelector
{
public:
    HtmlDescriptionLinesSelector();

    std::vector<std::string> selectLines(const std::string&) const override;

private:
    std::vector<std::string> selectGlossaryLines(const std::string&) const;

    std::unique_ptr<utils::HtmlTagsDeleter> htmlTagsDeleter;
};
}