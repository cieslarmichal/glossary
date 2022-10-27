#pragma once

#include "nlohmann/json.hpp"

#include "DictionarySerializer.h"

namespace glossary::dictionary
{
class DictionaryJsonSerializer : public DictionarySerializer
{
public:
    std::string serialize(const std::vector<Dictionary>&) const override;
    std::vector<Dictionary> deserialize(const std::string& jsonText) const override;
};
}
