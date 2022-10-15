#pragma once

#include "nlohmann/json.hpp"

#include "WordDescriptionResponseDeserializer.h"

namespace glossary::dictionary
{
class WordsApiJsonResponseDeserializer : public WordDescriptionResponseDeserializer
{
public:
    std::vector<std::string> deserializeDefinitions(const std::string&) const override;
    std::vector<std::string> deserializeExamples(const std::string&) const override;
    std::vector<std::string> deserializeSynonyms(const std::string&) const override;

private:
    std::vector<std::string> readDefinitions(const nlohmann::json&) const;
    std::vector<std::string> parseDefinitions(const nlohmann::json&) const;
    bool isJsonDefinitionValid(const nlohmann::json&) const;
    std::vector<std::string> readExamples(const nlohmann::json&) const;
    std::vector<std::string> readSynonyms(const nlohmann::json&) const;
};
}