#pragma once

#include "DescriptionParser.h"

namespace glossary::wordDescriptionDownloader
{
class DefaultDescriptionParser : public DescriptionParser
{
public:
    boost::optional<wordDescriptionRepository::Description>
    parse(const std::vector<std::string>&) const override;
};
}