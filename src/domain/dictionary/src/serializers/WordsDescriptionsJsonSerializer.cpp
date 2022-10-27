#include "WordsDescriptionsJsonSerializer.h"

#include <iostream>

#include "boost/algorithm/cxx11/all_of.hpp"

namespace glossary::dictionary
{
namespace
{
constexpr auto wordsDescriptionsField = "wordsDescriptions";
constexpr auto englishWordField = "englishWord";
constexpr auto definitionsField = "definitions";
constexpr auto examplesField = "examples";
constexpr auto synonymsField = "synonyms";
}

std::string WordsDescriptionsJsonSerializer::serialize(const WordsDescriptions& descriptions) const
{
    nlohmann::json serialized;
    for (const auto& wordDescription : descriptions)
    {
        serialized[wordsDescriptionsField].push_back(getJsonFromWordDescription(wordDescription));
    }
    if (serialized.empty())
    {
        return {};
    }
    return serialized.dump();
}

WordsDescriptions WordsDescriptionsJsonSerializer::deserialize(const std::string& jsonText) const
{
    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readWordsDescriptions(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse wordsDescriptions:" << e.what();
    }
    return {};
}

nlohmann::json
WordsDescriptionsJsonSerializer::getJsonFromWordDescription(const WordDescription& wordDescription) const
{
    nlohmann::json json;
    json[englishWordField] = wordDescription.englishWord;
    json[definitionsField] = wordDescription.definitions;
    json[examplesField] = wordDescription.examples;
    json[synonymsField] = wordDescription.synonyms;
    return json;
}

WordsDescriptions WordsDescriptionsJsonSerializer::readWordsDescriptions(const nlohmann::json& json) const
{
    if (json.find(wordsDescriptionsField) != json.end())
    {
        return parseWordsDescriptions(json[wordsDescriptionsField]);
    }
    std::cerr << "There are no wordsDescriptions stored";
    return {};
}

WordsDescriptions
WordsDescriptionsJsonSerializer::parseWordsDescriptions(const nlohmann::json& wordsDescriptionsJson) const
{
    WordsDescriptions wordsDescriptions;
    for (const auto& wordDescriptionData : wordsDescriptionsJson)
    {
        if (isWordDescriptionValid(wordDescriptionData))
        {
            WordDescription wordDescription{
                wordDescriptionData[englishWordField].get<std::string>(),
                wordDescriptionData[definitionsField].get<std::vector<std::string>>(),
                wordDescriptionData[examplesField].get<std::vector<std::string>>(),
                wordDescriptionData[synonymsField].get<std::vector<std::string>>()};
            wordsDescriptions.emplace_back(wordDescription);
        }
        else
        {
            std::cerr << "WordDescription does not contain all required data fields";
        }
    }

    return wordsDescriptions;
}

bool WordsDescriptionsJsonSerializer::isWordDescriptionValid(const nlohmann::json& wordDescriptionData) const
{
    const auto requiredFields = {englishWordField, definitionsField, examplesField, synonymsField};
    auto wordDescriptionValid = boost::algorithm::all_of(requiredFields, [&](const auto& fieldName) {
        return wordDescriptionData.find(fieldName) != wordDescriptionData.end();
    });
    return wordDescriptionValid;
}

}