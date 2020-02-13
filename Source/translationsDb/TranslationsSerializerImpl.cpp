#include "translationsDb/TranslationsSerializerImpl.h"

#include <iostream>

#include "boost/algorithm/cxx11/any_of.hpp"

namespace
{
constexpr auto translationsField = "translations";
constexpr auto polishWordField = "polishWord";
constexpr auto englishWordField = "englishWord";
}

namespace translationsDb
{

std::string
TranslationsSerializerImpl::serialize(const Translations& translations) const
{
    nlohmann::json serialized;
    for (const auto& translation : translations)
    {
        serialized[translationsField].push_back(
            getJsonFromTranslation(translation));
    }
    if (serialized.empty())
    {
        return {};
    }
    return serialized.dump();
}

Translations
TranslationsSerializerImpl::deserialize(const std::string& jsonText) const
{
    if (jsonText.empty())
    {
        return {};
    }

    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readTranslations(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse translations:" << e.what();
    }
    return {};
}

nlohmann::json TranslationsSerializerImpl::getJsonFromTranslation(
    const Translation& translation) const
{
    nlohmann::json val = nlohmann::json::object();
    val[polishWordField] = translation.polishWord;
    val[englishWordField] = translation.englishWord;
    return val;
}

Translations
TranslationsSerializerImpl::readTranslations(const nlohmann::json& json) const
{
    if (json.find(translationsField) != json.end())
    {
        return parseTranslations(json[translationsField]);
    }
    std::cerr << "There are no translations stored\n";
    return {};
}

Translations TranslationsSerializerImpl::parseTranslations(
    const nlohmann::json& translationsJson) const
{
    Translations translations;
    for (const auto& translationData : translationsJson)
    {
        if (isTranslationValid(translationData))
        {
            translations.emplace_back(
                Translation{translationData[polishWordField],
                            translationData[englishWordField]});
        }
        else
        {
            std::cerr << "translation does not contain all required data\n";
        }
    }
    return translations;
}

bool TranslationsSerializerImpl::isTranslationValid(
    const nlohmann::json& translationJson) const
{
    const auto requiredFields = {polishWordField, englishWordField};
    auto wordInvalid =
        boost::algorithm::any_of(requiredFields, [&](const auto& fieldName) {
            return translationJson.find(fieldName) == translationJson.end();
        });
    return !wordInvalid;
}

}