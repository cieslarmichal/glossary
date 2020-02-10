#include "translation/TranslationDeserializerImpl.h"

#include <iostream>

namespace translation
{

namespace
{
constexpr auto translationField = "text";
}

TranslatedText
TranslationDeserializerImpl::deserialize(const std::string& jsonText) const
{
    if (jsonText.empty())
    {
        return {};
    }

    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readTranslation(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse translation:" << e.what();
    }
    return {};
}

TranslatedText
TranslationDeserializerImpl::readTranslation(const nlohmann::json& json) const
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
    std::cerr << "There are no translations stored\n";
    return {};
}

}