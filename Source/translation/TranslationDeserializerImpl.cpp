#include "translation/TranslationDeserializerImpl.h"

#include <iostream>

namespace translation
{

namespace
{
constexpr auto translationField = "text";
}

std::string
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

std::string
TranslationDeserializerImpl::readTranslation(const nlohmann::json& json) const
{
    std::string translations;
    if (json.find(translationField) != json.end())
    {
        for (const auto& translation : json[translationField])
        {
            translations += translation;
        }
        return translations;
    }
    std::cerr << "There are no translations stored\n";
    return {};
}

}