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

private:
    nlohmann::json getJsonFromDescription(const Description&) const;
    nlohmann::json getJsonFromDefinitionAndExample(const DefinitionWithExample&) const;
    Description getDescriptionFromJson(const nlohmann::json&) const;
    DefinitionWithExample getDefinitionAndExampleFromJson(const nlohmann::json&) const;
};
}