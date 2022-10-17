#include "DefaultTranslationService.h"

#include <iostream>

#include "StringHelper.h"
#include "exceptions/InvalidApiKey.h"
#include "fmt/core.h"
#include "httpClient/HttpStatusCode.h"

namespace
{
const std::string urlAddress{"https://translation.googleapis.com/language/translate/v2"};
}

namespace glossary::translation
{
const std::vector<translation::Language> DefaultTranslationService::supportedLanguages{
    translation::Language::Polish, translation::Language::English};

DefaultTranslationService::DefaultTranslationService(
    std::shared_ptr<const common::httpClient::HttpClient> httpClientInit,
    std::unique_ptr<GoogleTranslateApiResponseDeserializer> deserializer)
    : httpClient{std::move(httpClientInit)}, translationDeserializer{std::move(deserializer)}
{
}

std::optional<std::string> DefaultTranslationService::translate(const std::string& sourceText,
                                                                Language sourceLanguage,
                                                                Language targetLanguage,
                                                                const std::string& apiKey) const
{
    if (sourceText.empty())
    {
        return std::nullopt;
    }

    const auto url = formatTranslationRequestUrl(sourceText, sourceLanguage, targetLanguage, apiKey);

    const auto response = httpClient->get({url});

    if (response.statusCode == common::httpClient::HttpStatusCode::Ok)
    {
        const auto googleTranslateApiResponse = translationDeserializer->deserialize(response.data);

        const auto translations = googleTranslateApiResponse.data.translations;

        if (translations.empty())
        {
            return std::nullopt;
        }

        return googleTranslateApiResponse.data.translations[0].translatedText;
    }
    else if (response.statusCode == common::httpClient::HttpStatusCode::BadRequest ||
             response.statusCode == common::httpClient::HttpStatusCode::Unauthorized)
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }

    std::cerr << "Error while translating text: " << sourceText;

    return std::nullopt;
}

std::string DefaultTranslationService::formatTranslationRequestUrl(const std::string& sourceText,
                                                                   Language sourceLanguage,
                                                                   Language targetLanguage,
                                                                   const std::string& apiKey) const
{
    const auto splitText = common::collection::split(sourceText, " ");

    const auto formattedSourceText = common::collection::join(splitText, "+");

    const auto keyField = "key=" + apiKey;

    const auto textField = "q=" + formattedSourceText;

    const auto sourceLanguageField = "source=" + toLanguageCode(sourceLanguage);

    const auto targetLanguageField = "target=" + toLanguageCode(targetLanguage);

    return fmt::format("{}?{}&{}&{}&{}", urlAddress, keyField, textField, sourceLanguageField,
                       targetLanguageField);
}

std::vector<Language> DefaultTranslationService::getSupportedLanguages() const
{
    return supportedLanguages;
}
}