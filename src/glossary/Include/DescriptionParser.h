#pragma once

#include "boost/optional.hpp"
#include "wordsDescriptionsDb/Description.h"

class DescriptionParser
{
public:
    virtual ~DescriptionParser() = default;

    virtual boost::optional<wordsDescriptionsDb::Description>
    parse(const std::vector<std::string>&) const = 0;
};
