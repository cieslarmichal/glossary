#pragma once

#include "TranslatorFactory.h"
#include "httpClient/HttpClient.h"

namespace glossary::translation
{
class DefaultTranslationServiceFactory : public TranslatorFactory
{
public:
    explicit DefaultTranslationServiceFactory(std::shared_ptr<const httpClient::HttpClient>);

    std::unique_ptr<TranslationService> createTranslator() const override;

private:
    std::shared_ptr<const httpClient::HttpClient> httpHandler;
};
}