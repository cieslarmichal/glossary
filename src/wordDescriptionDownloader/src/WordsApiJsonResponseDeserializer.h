#pragma once

#include "nlohmann/json.hpp"

#include "WordDescriptionResponseDeserializer.h"

namespace glossary::wordDescriptionDownloader
{
class WordsApiJsonResponseDeserializer : public WordDescriptionResponseDeserializer
{
public:
    wordDescriptionRepository::Definitions deserializeDefinitions(const std::string&) const override;
    wordDescriptionRepository::Examples deserializeExamples(const std::string&) const override;
    wordDescriptionRepository::Synonyms deserializeSynonyms(const std::string&) const override;

private:
    wordDescriptionRepository::Definitions readDefinitions(const nlohmann::json&) const;
    wordDescriptionRepository::Definitions parseDefinitions(const nlohmann::json&) const;
    bool isJsonDefinitionValid(const nlohmann::json&) const;
    wordDescriptionRepository::Examples readExamples(const nlohmann::json&) const;
    wordDescriptionRepository::Synonyms readSynonyms(const nlohmann::json&) const;
};
}