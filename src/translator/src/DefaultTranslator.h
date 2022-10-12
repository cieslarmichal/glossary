#pragma once

#include <memory>

#include "TranslationDeserializer.h"
#include "TranslationRequestFormatter.h"
#include "Translator.h"
#include "httpClient/HttpClient.h"

namespace glossary::translator
{
class DefaultTranslator : public Translator
{
public:
    DefaultTranslator(std::shared_ptr<const httpClient::HttpClient>, std::unique_ptr<TranslationDeserializer>,
                      std::unique_ptr<TranslationRequestFormatter>);

    boost::optional<TranslatedText> translate(const std::string&, Language sourceLanguage,
                                              Language targetLanguage,
                                              const std::string& apiKey) const override;

private:
    httpClient::HttpResponse tryGetResponseFromTranslationApi(const std::string&) const;
    bool translationSucceeded(int statusCode) const;
    bool translationFailedDueToInvalidApiKey(int) const;

    std::shared_ptr<const httpClient::HttpClient> httpHandler;
    std::unique_ptr<TranslationDeserializer> translationDeserializer;
    std::unique_ptr<TranslationRequestFormatter> requestFormatter;
};
}