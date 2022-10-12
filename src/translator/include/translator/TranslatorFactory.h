#pragma once

#include <memory>

#include "Translator.h"
#include "TranslatorApi.h"
#include "httpClient/HttpClient.h"

namespace glossary::translator
{
class TRANSLATOR_API TranslatorFactory
{
public:
    virtual ~TranslatorFactory() = default;

    virtual std::unique_ptr<Translator> createTranslator() const = 0;

    static std::unique_ptr<TranslatorFactory>
    createTranslatorFactory(const std::shared_ptr<const httpClient::HttpClient>&);
};
}