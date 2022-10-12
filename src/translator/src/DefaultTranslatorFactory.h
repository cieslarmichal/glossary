#pragma once

#include "TranslatorFactory.h"
#include "httpClient/HttpClient.h"

namespace glossary::translator
{
class DefaultTranslatorFactory : public TranslatorFactory
{
public:
    explicit DefaultTranslatorFactory(std::shared_ptr<const httpClient::HttpClient>);

    std::unique_ptr<Translator> createTranslator() const override;

private:
    std::shared_ptr<const httpClient::HttpClient> httpHandler;
};
}