#pragma once

#include "WordDescription.h"
#include "boost/optional.hpp"

class WordDescriptionParser
{
public:
    boost::optional<WordDescription> parse(const std::vector<std::string>&) const;
};
