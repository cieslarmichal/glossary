#pragma once

#include "Description.h"
#include "boost/optional.hpp"

namespace wordsDb::descriptionsDb
{

class WordDescriptionParser
{
public:
    boost::optional<Description> parse(const std::vector<std::string>&) const;
};
}