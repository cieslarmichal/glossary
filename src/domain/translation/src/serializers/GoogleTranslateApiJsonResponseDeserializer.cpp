#include "GoogleTranslateApiJsonResponseDeserializer.h"

#include "nlohmann/json.hpp"

#include "exceptions/GoogleTranslateApiJsonResponseMissingRequiredFieldsError.h"
#include "exceptions/InvalidJsonError.h"

namespace glossary::translation
{
namespace
{
nlohmann::json parseJsonText(const std::string& jsonText);
void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName);

constexpr auto dataField = "data";
constexpr auto translationsField = "translations";
constexpr auto translatedTextField = "translatedText";
constexpr auto detectedSourceLanguageField = "detectedSourceLanguage";
}

GoogleTranslateApiResponse
GoogleTranslateApiJsonResponseDeserializer::deserialize(const std::string& responseJsonBody) const
{
    const auto json = parseJsonText(responseJsonBody);

    if (json.empty())
    {
        return {};
    }

    validateFieldExistence(json, dataField);

    const auto& dataJson = json[dataField];

    validateFieldExistence(dataJson, translationsField);

    const auto& translationsJson = dataJson[translationsField];

    std::vector<GoogleTranslateApiResponseDataTranslation> translations;

    for (const auto& translationJson : translationsJson)
    {
        validateFieldExistence(translationJson, translatedTextField);
        validateFieldExistence(translationJson, detectedSourceLanguageField);

        const auto& translatedText = translationJson[translatedTextField].get<std::string>();
        const auto& detectedSourceLanguage = translationJson[detectedSourceLanguageField].get<std::string>();

        translations.push_back({translatedText, detectedSourceLanguage});
    }

    return {translations};
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
        throw exceptions::GoogleTranslateApiJsonResponseMissingRequiredFieldsError{
            fmt::format("Missing {} field.", fieldName)};
    }
}
}
}