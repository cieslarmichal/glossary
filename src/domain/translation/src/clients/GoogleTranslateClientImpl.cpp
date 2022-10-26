#include "GoogleTranslateClientImpl.h"

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "collection/StringHelper.h"
#include "exceptions/GoogleTranslateApiError.h"
#include "exceptions/GoogleTranslateApiJsonResponseMissingRequiredFieldsError.h"
#include "exceptions/InvalidJsonError.h"
#include "httpClient/HttpStatusCode.h"

namespace glossary::translation
{
namespace
{
nlohmann::json parseJsonText(const std::string& jsonText);
void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName);

constexpr auto translateEndpoint = "/language/translate/v2";
constexpr auto dataField = "data";
constexpr auto translationsField = "translations";
constexpr auto translatedTextField = "translatedText";
constexpr auto detectedSourceLanguageField = "detectedSourceLanguage";
}

GoogleTranslateClientImpl::GoogleTranslateClientImpl(
    std::shared_ptr<const common::httpClient::HttpClient> httpClientInit,
    GoogleTranslateClientConfig configInit)
    : httpClient{std::move(httpClientInit)}, config(std::move(configInit))
{
}

std::optional<std::string> GoogleTranslateClientImpl::translate(const TranslatePayload& payload) const
{
    const auto httpGetRequestPayload = prepareRequestPayload(payload);

    const auto response = httpClient->get(httpGetRequestPayload);

    if (response.statusCode != common::httpClient::HttpStatusCode::Ok)
    {
        throw exceptions::GoogleTranslateApiError{response.data};
    }

    const auto googleTranslateApiResponse = parseGoogleTranslateResponseBody(response.data);

    const auto translations = googleTranslateApiResponse.data.translations;

    if (translations.empty())
    {
        return std::nullopt;
    }

    return translations[0].translatedText;
}

common::httpClient::HttpGetRequestPayload
GoogleTranslateClientImpl::prepareRequestPayload(const TranslatePayload& payload) const
{
    const auto splitText = common::collection::split(payload.text, " ");
    const auto formattedText = common::collection::join(splitText, "+");

    const auto headers = std::nullopt;

    const std::map<std::string, std::string> queries{{"key", config.googleTranslateApiKey},
                                                     {"q", formattedText},
                                                     {"source", toLanguageCode(payload.sourceLanguage)},
                                                     {"target", toLanguageCode(payload.targetLanguage)}};

    const auto urlAddress = fmt::format("{}{}", config.googleTranslateBaseUrl, translateEndpoint);

    return {urlAddress, headers, queries};
}

GoogleTranslateApiResponse
GoogleTranslateClientImpl::parseGoogleTranslateResponseBody(const std::string& responseBody) const
{
    const auto json = parseJsonText(responseBody);

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
