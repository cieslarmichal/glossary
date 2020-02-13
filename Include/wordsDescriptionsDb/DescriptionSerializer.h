#pragma once

#include "Description.h"
#include "nlohmann/json.hpp"

namespace wordsDescriptionsDb
{

class DescriptionSerializer
{
public:
    nlohmann::json serialize(const Description&) const;
    Description deserialize(const nlohmann::json&) const;
};
}