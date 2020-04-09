#include "DefaultTranslatorFactory.h"

#include "DefaultTranslator.h"
#include "GoogleTranslateApiJsonResponseDeserializer.h"
#include "GoogleTranslateApiRequestFormatter.h"

namespace glossary::translator
{
DefaultTranslatorFactory::DefaultTranslatorFactory(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

std::unique_ptr<Translator> DefaultTranslatorFactory::createTranslator() const
{
    return std::make_unique<DefaultTranslator>(httpHandler,
                                               std::make_unique<GoogleTranslateApiJsonResponseDeserializer>(),
                                               std::make_unique<GoogleTranslateApiRequestFormatter>());
}

}