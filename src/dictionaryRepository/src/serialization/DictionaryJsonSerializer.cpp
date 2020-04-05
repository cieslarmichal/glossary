#include "DictionaryJsonSerializer.h"

#include <iostream>

#include "boost/algorithm/cxx11/all_of.hpp"

namespace glossary::dictionaryService
{
namespace
{
constexpr auto dictionaryNameField = "dictionaryName";
constexpr auto dictionaryWordsField = "dictionaryWords";
constexpr auto englishWordField = "englishWord";
constexpr auto translationField = "translation";
}

std::string DictionaryJsonSerializer::serialize(const Dictionaries& dictionaries) const
{
    nlohmann::json serializedDictionaries = nlohmann::json::array();
    for (const auto& dictionary : dictionaries)
    {
        serializedDictionaries.push_back(getJsonFromDictionary(dictionary));
    }
    if (serializedDictionaries.empty())
    {
        return {};
    }
    return serializedDictionaries.dump();
}

Dictionaries DictionaryJsonSerializer::deserialize(const std::string& serializedDictionaries) const
{
    try
    {
        const auto json = nlohmann::json::parse(serializedDictionaries);
        return getDictionariesFromJson(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to deserialize dictionaries:" << e.what();
    }
    return {};
}

nlohmann::json DictionaryJsonSerializer::getJsonFromDictionary(const Dictionary& dictionary) const
{
    nlohmann::json dictionaryJson;
    dictionaryJson[dictionaryNameField] = dictionary.name;
    dictionaryJson[dictionaryWordsField] = getJsonFromDictionaryWords(dictionary.words);
    return dictionaryJson;
}

nlohmann::json DictionaryJsonSerializer::getJsonFromDictionaryWords(const DictionaryWords& words) const
{
    nlohmann::json dictionaryWordsJson = nlohmann::json::array();
    for (const auto& word : words)
    {
        dictionaryWordsJson.emplace_back(getJsonFromDictionaryWord(word));
    }
    return dictionaryWordsJson;
}

nlohmann::json DictionaryJsonSerializer::getJsonFromDictionaryWord(const DictionaryWord& dictionaryWord) const
{
    nlohmann::json dictionaryWordJson;
    dictionaryWordJson[englishWordField] = dictionaryWord.englishWord;
    if (dictionaryWord.translation)
    {
        dictionaryWordJson[translationField] = *dictionaryWord.translation;
    }
    return dictionaryWordJson;
}

Dictionaries DictionaryJsonSerializer::getDictionariesFromJson(const nlohmann::json& json) const
{
    Dictionaries dictionariesFromJson{};
    for (const auto& dictionary : json)
    {
        if (isDictionaryValid(dictionary))
        {
            dictionariesFromJson.emplace_back(getDictionaryFromJson(dictionary));
        }
    }
    return dictionariesFromJson;
}

Dictionary DictionaryJsonSerializer::getDictionaryFromJson(const nlohmann::json& dictionaryJson) const
{
    return Dictionary{dictionaryJson[dictionaryNameField].get<std::string>(),
                      getDictionaryWordsFromJson(dictionaryJson[dictionaryWordsField])};
}

DictionaryWords
DictionaryJsonSerializer::getDictionaryWordsFromJson(const nlohmann::json& dictionaryWordsJson) const
{
    DictionaryWords dictionaryWordsFromJson{};
    for (const auto& dictionaryWordJson : dictionaryWordsJson)
    {
        if (isDictionaryWordValid(dictionaryWordJson))
        {
            dictionaryWordsFromJson.emplace_back(getDictionaryWordFromJson(dictionaryWordJson));
        }
    }
    return dictionaryWordsFromJson;
}

DictionaryWord
DictionaryJsonSerializer::getDictionaryWordFromJson(const nlohmann::json& dictionaryWordJson) const
{
    if (dictionaryWordJson.find(translationField) != dictionaryWordJson.end())
    {
        return DictionaryWord{dictionaryWordJson[englishWordField].get<std::string>(),
                              dictionaryWordJson[translationField].get<std::string>()};
    }
    return DictionaryWord{dictionaryWordJson[englishWordField].get<std::string>(), boost::none};
}

bool DictionaryJsonSerializer::isDictionaryValid(const nlohmann::json& dictionaryData) const
{
    const auto requiredFields = {dictionaryNameField, dictionaryWordsField};
    auto dictionaryValid = boost::algorithm::all_of(requiredFields, [&](const auto& fieldName) {
        return dictionaryData.find(fieldName) != dictionaryData.end();
    });
    return dictionaryValid;
}

bool DictionaryJsonSerializer::isDictionaryWordValid(const nlohmann::json& dictionaryWordData) const
{
    return dictionaryWordData.find(englishWordField) != dictionaryWordData.end();
}

}