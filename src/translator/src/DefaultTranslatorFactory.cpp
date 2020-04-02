#include "DefaultTranslatorFactory.h"

#include "DefaultTranslator.h"
#include "TranslationJsonDeserializer.h"
#include "TranslationYandexRequestFormatter.h"

namespace glossary::translator
{
DefaultTranslatorFactory::DefaultTranslatorFactory(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

std::unique_ptr<Translator> DefaultTranslatorFactory::createTranslator() const
{
    return std::make_unique<DefaultTranslator>(httpHandler, std::make_unique<TranslationJsonDeserializer>(),
                                               std::make_unique<TranslationYandexRequestFormatter>());
}

}