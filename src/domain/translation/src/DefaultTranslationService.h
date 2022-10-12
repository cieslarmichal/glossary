#pragma once

#include <memory>

#include "TranslationDeserializer.h"
#include "TranslationService.h"
#include "httpClient/HttpClient.h"

namespace glossary::translation
{
class DefaultTranslationService : public TranslationService
{
public:
    DefaultTranslationService(std::shared_ptr<const httpClient::HttpClient>,
                              std::unique_ptr<TranslationDeserializer>);

    std::optional<std::string> translate(const std::string&, Language sourceLanguage, Language targetLanguage,
                                         const std::string& apiKey) const override;
    std::vector<Language> getSupportedLanguages() const override;

private:
    std::string formatTranslationRequestUrl(const std::string&, Language sourceLanguage,
                                            Language targetLanguage, const std::string& apiKey) const;

    std::shared_ptr<const httpClient::HttpClient> httpClient;
    std::unique_ptr<TranslationDeserializer> translationDeserializer;

    static const std::vector<translation::Language> supportedLanguages;
};
}