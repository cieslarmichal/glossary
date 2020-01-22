#pragma once

#include "DescriptionsSerializer.h"
#include "WordDescriptionSerializer.h"
#include "nlohmann/json.hpp"

namespace wordsDb::descriptionsDb
{
class DescriptionsSerializerImpl : public DescriptionsSerializer
{
public:
    std::string serialize(const Words&) const override;
    Words deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromWord(const WordDescription&) const;
    Words readWords(const nlohmann::json&) const;
    Words parseWords(const nlohmann::json&) const;
    bool isWordValid(const nlohmann::json&) const;

    WordDescriptionSerializer wordDescriptionSerializer;
};
}
