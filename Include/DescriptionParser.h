#pragma once

#include "boost/optional.hpp"
#include "wordsDb/wordsDescriptionsDb/Description.h"

using namespace wordsDb::wordsDescriptionsDb;

class DescriptionParser
{
public:
    boost::optional<Description> parse(const std::vector<std::string>&) const;
};
