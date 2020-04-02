#include "TranslationJsonDeserializer.h"

#include <iostream>

namespace glossary::translator
{
namespace
{
constexpr auto translationField = "text";
}

TranslatedText TranslationJsonDeserializer::deserialize(const std::string& jsonText) const
{
    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readTranslation(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse translated text:" << e.what();
    }
    return {};
}

TranslatedText TranslationJsonDeserializer::readTranslation(const nlohmann::json& json) const
{
    TranslatedText translatedText;
    if (json.find(translationField) != json.end())
    {
        for (const auto& translation : json[translationField])
        {
            translatedText += translation;
        }
        return translatedText;
    }
    std::cerr << "There are no translations texts";
    return {};
}

}