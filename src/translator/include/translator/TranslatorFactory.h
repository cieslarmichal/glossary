#pragma once

#include <memory>

#include "Translator.h"
#include "webConnection/HttpHandler.h"

namespace translator
{
class TranslatorFactory
{
public:
    virtual ~TranslatorFactory() = default;

    virtual std::unique_ptr<Translator> createTranslator() const = 0;

    static std::unique_ptr<TranslatorFactory>
    createTranslatorFactory(const std::shared_ptr<webConnection::HttpHandler>&);
};
}