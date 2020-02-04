#pragma once

#include "DescriptionParser.h"

using namespace wordsDb::wordsDescriptionsDb;

class DescriptionParserImpl : public DescriptionParser
{
public:
    boost::optional<Description> parse(const std::vector<std::string>&) const override;
};
