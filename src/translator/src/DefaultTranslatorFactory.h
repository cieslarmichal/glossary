#pragma once

#include "TranslatorFactory.h"
#include "webConnection/HttpHandler.h"

namespace glossary::translator
{
class DefaultTranslatorFactory : public TranslatorFactory
{
public:
    explicit DefaultTranslatorFactory(std::shared_ptr<const webConnection::HttpHandler>);

    std::unique_ptr<Translator> createTranslator() const override;

private:
    std::shared_ptr<const webConnection::HttpHandler> httpHandler;
};
}