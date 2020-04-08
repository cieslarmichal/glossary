#include "GoogleTranslateApiJsonResponseDeserializer.h"

#include <iostream>

namespace glossary::translator
{
namespace
{
constexpr auto dataField = "data";
constexpr auto translationsField = "translations";
constexpr auto translatedTextField = "translatedText";
}

TranslatedText GoogleTranslateApiJsonResponseDeserializer::deserialize(const std::string& jsonText) const
{
    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readData(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse translated text:" << e.what();
        return {};
    }
}

TranslatedText GoogleTranslateApiJsonResponseDeserializer::readData(const nlohmann::json& json) const
{
    TranslatedText translatedText;
    if (json.find(dataField) != json.end())
    {
        return readTranslatedText(json[dataField]);
    }
    std::cerr << "There are no data";
    return {};
}

TranslatedText
GoogleTranslateApiJsonResponseDeserializer::readTranslatedText(const nlohmann::json& json) const
{
    TranslatedText translatedText;

    for (const auto& translationJson : json[translationsField])
    {
        if (translationJson.find(translatedTextField) != translationJson.end())
            translatedText += translationJson[translatedTextField].get<std::string>();
    }

    return translatedText;
}

}