#include "WordsDescriptionsJsonSerializer.h"

#include <iostream>

#include "boost/algorithm/cxx11/all_of.hpp"

namespace glossary::wordDescriptionRepository
{
namespace
{
constexpr auto wordsDescriptionsField = "wordsDescriptions";
constexpr auto englishWordField = "englishWord";
constexpr auto definitionsWithExamplesField = "definitionsWithExamples";
constexpr auto definitionField = "definition";
constexpr auto examplesField = "examples";
constexpr auto sentencesField = "sentences";
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
    json[definitionsWithExamplesField] =
        getJsonFromDefinitionsWithExamples(wordDescription.definitionsWithExamples);
    json[sentencesField] = wordDescription.sentences;
    return json;
}

nlohmann::json WordsDescriptionsJsonSerializer::getJsonFromDefinitionsWithExamples(
    const DefinitionsWithExamples& definitionsWithExamples) const
{
    nlohmann::json json = nlohmann::json::array();
    for (const auto& definitionWithExample : definitionsWithExamples)
    {
        json.push_back(getJsonFromDefinitionWithExample(definitionWithExample));
    }
    return json;
}

nlohmann::json WordsDescriptionsJsonSerializer::getJsonFromDefinitionWithExample(
    const DefinitionWithExample& definitionWithExample) const
{
    nlohmann::json json;
    json[definitionField] = definitionWithExample.definition;
    json[examplesField] = definitionWithExample.examples;
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
                parseDefinitionsWithExamples(wordDescriptionData[definitionsWithExamplesField]),
                wordDescriptionData[sentencesField].get<std::vector<std::string>>()};
            wordsDescriptions.emplace_back(wordDescription);
        }
        else
        {
            std::cerr << "WordDescription does not contain all required data fields";
        }
    }

    return wordsDescriptions;
}

DefinitionsWithExamples WordsDescriptionsJsonSerializer::parseDefinitionsWithExamples(
    const nlohmann::json& definitionsWithExamplesJson) const
{
    DefinitionsWithExamples definitionsWithExamples;
    for (const auto& definitionWithExampleData : definitionsWithExamplesJson)
    {
        if (isDefinitionsWithExamplesValid(definitionWithExampleData))
        {
            DefinitionWithExample definitionWithExample{
                definitionWithExampleData[definitionField].get<std::string>(),
                definitionWithExampleData[examplesField].get<std::vector<std::string>>()};
            definitionsWithExamples.emplace_back(definitionWithExample);
        }
        else
        {
            std::cerr << "DefinitionWithExample does not contain all required data fields";
        }
    }
    return definitionsWithExamples;
}

bool WordsDescriptionsJsonSerializer::isWordDescriptionValid(const nlohmann::json& wordDescriptionData) const
{
    const auto requiredFields = {englishWordField, definitionsWithExamplesField, sentencesField};
    auto wordDescriptionValid = boost::algorithm::all_of(requiredFields, [&](const auto& fieldName) {
        return wordDescriptionData.find(fieldName) != wordDescriptionData.end();
    });
    return wordDescriptionValid;
}

bool WordsDescriptionsJsonSerializer::isDefinitionsWithExamplesValid(
    const nlohmann::json& definitionsWithExamplesData) const
{
    const auto requiredFields = {definitionField, examplesField};
    auto definitionsWithExamplesValid = boost::algorithm::all_of(requiredFields, [&](const auto& fieldName) {
        return definitionsWithExamplesData.find(fieldName) != definitionsWithExamplesData.end();
    });
    return definitionsWithExamplesValid;
}
}