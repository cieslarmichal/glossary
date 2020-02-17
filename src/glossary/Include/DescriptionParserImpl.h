#pragma once

#include "DescriptionParser.h"

class DescriptionParserImpl : public DescriptionParser
{
public:
    boost::optional<wordsDescriptionsDb::Description>
    parse(const std::vector<std::string>&) const override;
};
