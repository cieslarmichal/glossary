#pragma once

#include "DescriptionParser.h"

namespace wordDescriptionDownloader
{
class DefaultDescriptionParser : public DescriptionParser
{
public:
    //TODO: remove duplicates
    boost::optional<wordsDescriptionsDb::Description> parse(const std::vector<std::string>&) const override;
};
}