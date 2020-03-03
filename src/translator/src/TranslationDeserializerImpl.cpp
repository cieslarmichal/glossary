#include "TranslationDeserializerImpl.h"

#include "plog/Log.h"

namespace translator
{

namespace
{
constexpr auto translationField = "text";
}

TranslatedText TranslationDeserializerImpl::deserialize(const std::string& jsonText) const
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
        LOG_WARNING << "Unable to parse translated text:" << e.what();
    }
    return {};
}

TranslatedText TranslationDeserializerImpl::readTranslation(const nlohmann::json& json) const
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
    LOG_WARNING << "There are no translations texts\n";
    return {};
}

}