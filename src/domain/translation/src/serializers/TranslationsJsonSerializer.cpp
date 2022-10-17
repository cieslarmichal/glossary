#include "TranslationsJsonSerializer.h"

#include "nlohmann/json.hpp"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/TranslationJsonMissingRequiredFieldsError.h"
#include "fmt/core.h"

namespace glossary::translation
{
namespace
{
nlohmann::json parseJsonText(const std::string& jsonText);
void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName);

constexpr auto translationsField = "translations";
constexpr auto polishWordField = "polishWord";
constexpr auto englishWordField = "englishWord";
}

std::string TranslationsJsonSerializer::serialize(const std::vector<Translation>& translations) const
{
    nlohmann::json serialized;

    for (const auto& translation : translations)
    {
        auto jsonTranslation = nlohmann::json::object();

        jsonTranslation[polishWordField] = translation.sourceText;

        jsonTranslation[englishWordField] = translation.translatedText;

        serialized[translationsField].push_back(jsonTranslation);
    }

    return serialized.empty() ? "{}" : serialized.dump();
}

std::vector<Translation> TranslationsJsonSerializer::deserialize(const std::string& jsonText) const
{
    const auto json = parseJsonText(jsonText);

    if (json.empty())
    {
        return {};
    }

    validateFieldExistence(json, translationsField);

    std::vector<Translation> translations;

    for (const auto& translationData : json[translationsField])
    {
        validateFieldExistence(translationData, polishWordField);

        validateFieldExistence(translationData, englishWordField);

        translations.emplace_back(Translation{translationData[polishWordField].get<std::string>(),
                                              translationData[englishWordField].get<std::string>()});
    }

    return translations;
}

namespace
{
nlohmann::json parseJsonText(const std::string& jsonText)
{
    try
    {
        return nlohmann::json::parse(jsonText);
    }
    catch (const std::exception& e)
    {
        throw exceptions::InvalidJsonError{e.what()};
    }
}

void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName)
{
    if (data.find(fieldName) == data.end())
    {
        throw exceptions::TranslationJsonMissingRequiredFieldsError{
            fmt::format("Missing {} field.", fieldName)};
    }
}
}

}
