#include "TranslationsSerializerImpl.h"

#include "boost/algorithm/cxx11/all_of.hpp"
#include "plog/Log.h"

namespace
{
constexpr auto translationsField = "translations";
constexpr auto polishWordField = "polishWord";
constexpr auto englishWordField = "englishWord";
}

namespace translationsDb
{

std::string TranslationsSerializerImpl::serialize(const Translations& translations) const
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

Translations TranslationsSerializerImpl::deserialize(const std::string& jsonText) const
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
        LOG_WARNING << "Unable to parse translations:" << e.what();
    }
    return {};
}

nlohmann::json TranslationsSerializerImpl::getJsonFromTranslation(const Translation& translation) const
{
    nlohmann::json val = nlohmann::json::object();
    val[polishWordField] = translation.sourceText;
    val[englishWordField] = translation.translatedText;
    return val;
}

Translations TranslationsSerializerImpl::readTranslations(const nlohmann::json& json) const
{
    if (json.find(translationsField) != json.end())
    {
        return parseTranslations(json[translationsField]);
    }
    LOG_WARNING << "There are no translations stored\n";
    return {};
}

Translations TranslationsSerializerImpl::parseTranslations(const nlohmann::json& translationsJson) const
{
    Translations translations;
    for (const auto& translationData : translationsJson)
    {
        if (isTranslationValid(translationData))
        {
            translations.emplace_back(
                Translation{translationData[polishWordField], translationData[englishWordField]});
        }
        else
        {
            LOG_WARNING << "WordStatistics does not contain all required data\n";
        }
    }
    return translations;
}

bool TranslationsSerializerImpl::isTranslationValid(const nlohmann::json& translationJson) const
{
    const auto requiredFields = {polishWordField, englishWordField};
    auto translationValid = boost::algorithm::all_of(requiredFields, [&](const auto& fieldName) {
        return translationJson.find(fieldName) != translationJson.end();
    });
    return translationValid;
}

}