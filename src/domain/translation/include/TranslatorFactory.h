#pragma once

#include <memory>

#include "TranslationService.h"
#include "httpClient/HttpClient.h"

namespace glossary::translation
{
class TranslatorFactory
{
public:
    virtual ~TranslatorFactory() = default;

    virtual std::unique_ptr<TranslationService> createTranslator() const = 0;

    static std::unique_ptr<TranslatorFactory>
    createTranslatorFactory(const std::shared_ptr<const httpClient::HttpClient>&);
};
}