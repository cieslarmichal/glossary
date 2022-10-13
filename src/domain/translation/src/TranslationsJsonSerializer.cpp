#include "TranslationsJsonSerializer.h"

#include <iostream>

#include "boost/algorithm/cxx11/all_of.hpp"

namespace glossary::translation
{
namespace
{
constexpr auto translationsField = "translations";
constexpr auto polishWordField = "polishWord";
constexpr auto englishWordField = "englishWord";
}

std::string TranslationsJsonSerializer::serialize(const std::vector<Translation>& translations) const
{
    nlohmann::json serialized;

    for (const auto& translation : translations)
    {
        serialized[translationsField].push_back(getJsonFromTranslation(translation));
    }

    if (serialized.empty())
    {
        return {};
    }

    return serialized.dump();
}

std::vector<Translation> TranslationsJsonSerializer::deserialize(const std::string& jsonText) const
{
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

nlohmann::json TranslationsJsonSerializer::getJsonFromTranslation(const Translation& translation) const
{
    nlohmann::json val = nlohmann::json::object();

    val[polishWordField] = translation.sourceText;

    val[englishWordField] = translation.translatedText;

    return val;
}

std::vector<Translation> TranslationsJsonSerializer::readTranslations(const nlohmann::json& json) const
{
    if (json.find(translationsField) != json.end())
    {
        return parseTranslations(json[translationsField]);
    }

    std::cerr << "There are no translations stored\n";

    return {};
}

std::vector<Translation>
TranslationsJsonSerializer::parseTranslations(const nlohmann::json& translationsJson) const
{
    std::vector<Translation> translations;

    for (const auto& translationData : translationsJson)
    {
        if (isTranslationValid(translationData))
        {
            translations.emplace_back(Translation{translationData[polishWordField].get<std::string>(),
                                                  translationData[englishWordField].get<std::string>()});
        }
        else
        {
            std::cerr << "WordStatistics does not contain all required data\n";
        }
    }

    return translations;
}

bool TranslationsJsonSerializer::isTranslationValid(const nlohmann::json& translationJson) const
{
    const auto requiredFields = {polishWordField, englishWordField};

    auto translationValid =
        boost::algorithm::all_of(requiredFields, [&](const auto& fieldName)
                                 { return translationJson.find(fieldName) != translationJson.end(); });

    return translationValid;
}

}