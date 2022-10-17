#pragma once

#include <memory>

#include "../serializers/GoogleTranslateApiResponseDeserializer.h"
#include "TranslationService.h"
#include "httpClient/HttpClient.h"

namespace glossary::translation
{
class DefaultTranslationService : public TranslationService
{
public:
    DefaultTranslationService(std::shared_ptr<const common::httpClient::HttpClient>,
                              std::unique_ptr<GoogleTranslateApiResponseDeserializer>);

    std::optional<std::string> translate(const std::string& sourceText, Language sourceLanguage,
                                         Language targetLanguage, const std::string& apiKey) const override;
    std::vector<Language> getSupportedLanguages() const override;

private:
    std::shared_ptr<const common::httpClient::HttpClient> httpClient;
    std::unique_ptr<GoogleTranslateApiResponseDeserializer> translationDeserializer;

    static const std::vector<translation::Language> supportedLanguages;
};
}