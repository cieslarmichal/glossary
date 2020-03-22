#pragma once

#include "nlohmann/json.hpp"

#include "DescriptionSerializer.h"
#include "WordsDescriptionsSerializer.h"

namespace wordDescriptionRepository
{
class WordsDescriptionsJsonSerializer : public WordsDescriptionsSerializer
{
public:
    std::string serialize(const WordsDescriptions&) const override;
    WordsDescriptions deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromWordDescription(const WordDescription&) const;
    WordsDescriptions readWordsDescriptions(const nlohmann::json&) const;
    WordsDescriptions parseWordsDescriptions(const nlohmann::json&) const;
    bool isWordDescriptionValid(const nlohmann::json&) const;

    DescriptionSerializer wordDescriptionSerializer;
};
}
