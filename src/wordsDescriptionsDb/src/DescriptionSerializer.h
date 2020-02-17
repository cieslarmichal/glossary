#pragma once

#include "nlohmann/json.hpp"
#include "Description.h"

namespace wordsDescriptionsDb
{

class DescriptionSerializer
{
public:
    nlohmann::json serialize(const Description&) const;
    Description deserialize(const nlohmann::json&) const;
};
}