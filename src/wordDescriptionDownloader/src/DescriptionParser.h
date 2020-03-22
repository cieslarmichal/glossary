#pragma once

#include "boost/optional.hpp"

#include "wordDescriptionRepository/Description.h"

namespace wordDescriptionDownloader
{
class DescriptionParser
{
public:
    virtual ~DescriptionParser() = default;

    virtual boost::optional<wordDescriptionRepository::Description>
    parse(const std::vector<std::string>&) const = 0;
};
}