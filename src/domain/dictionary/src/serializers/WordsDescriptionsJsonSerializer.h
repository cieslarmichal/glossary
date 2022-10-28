#pragma once

#include "nlohmann/json.hpp"

#include "WordsDescriptionsSerializer.h"

namespace glossary::dictionary
{
class WordsDescriptionsJsonSerializer : public WordsDescriptionsSerializer
{
public:
    std::string serialize(const std::vector<WordDescription>&) const override;
    std::vector<WordDescription> deserialize(const std::string&) const override;
};
}
