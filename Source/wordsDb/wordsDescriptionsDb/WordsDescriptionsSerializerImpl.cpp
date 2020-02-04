#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsSerializerImpl.h"

#include <iostream>

#include "boost/algorithm/cxx11/any_of.hpp"

namespace
{
constexpr auto wordsDescriptionsField = "wordsDescriptions";
constexpr auto englishWordField = "englishWord";
constexpr auto polishWordField = "polishWord";
constexpr auto descriptionField = "description";
}

namespace wordsDb::wordsDescriptionsDb
{
std::string WordsDescriptionsSerializerImpl::serialize(
    const WordsDescriptions& descriptions) const
{
    nlohmann::json serialized;
    for (const auto& wordDescription : descriptions)
    {
        serialized[wordsDescriptionsField].push_back(
            getJsonFromWordDescription(wordDescription));
    }
    if (serialized.empty())
    {
        return {};
    }
    return serialized.dump();
}

WordsDescriptions
WordsDescriptionsSerializerImpl::deserialize(const std::string& jsonText) const
{
    if (jsonText.empty())
    {
        return {};
    }

    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readWordsDescriptions(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse wordDescriptions:" << e.what();
    }
    return {};
}

nlohmann::json WordsDescriptionsSerializerImpl::getJsonFromWordDescription(
    const WordDescription& wordDescription) const
{
    nlohmann::json val = nlohmann::json::object();
    val[englishWordField] = wordDescription.englishWord;
    val[polishWordField] = wordDescription.polishWord;
    val[descriptionField] =
        wordDescriptionSerializer.serialize(wordDescription.description);
    return val;
}

WordsDescriptions WordsDescriptionsSerializerImpl::readWordsDescriptions(
    const nlohmann::json& json) const
{
    if (json.find(wordsDescriptionsField) != json.end())
    {
        return parseWordsDescriptions(json[wordsDescriptionsField]);
    }
    std::cerr << "There are no wordsDescriptions stored\n";
    return {};
}

WordsDescriptions WordsDescriptionsSerializerImpl::parseWordsDescriptions(
    const nlohmann::json& wordsDescriptionsJson) const
{
    WordsDescriptions wordsDescriptions;
    for (const auto& wordDescriptionData : wordsDescriptionsJson)
    {
        if (isWordDescriptionValid(wordDescriptionData))
        {
            const EnglishWord englishWord{
                std::string(wordDescriptionData[englishWordField])};
            const PolishWord polishWord{
                std::string(wordDescriptionData[polishWordField])};
            const Description wordDescription{
                wordDescriptionSerializer.deserialize(
                    wordDescriptionData[descriptionField])};
            wordsDescriptions.push_back(
                {englishWord, polishWord, wordDescription});
        }
        else
        {
            std::cerr << "WordDescription does not contain all required data\n";
        }
    }
    return wordsDescriptions;
}

bool WordsDescriptionsSerializerImpl::isWordDescriptionValid(
    const nlohmann::json& wordDescriptionData) const
{
    const auto requiredFields = {englishWordField, polishWordField,
                                 descriptionField};
    auto wordInvalid =
        boost::algorithm::any_of(requiredFields, [&](const auto& fieldName) {
            return wordDescriptionData.find(fieldName) ==
                   wordDescriptionData.end();
        });
    return !wordInvalid;
}
}