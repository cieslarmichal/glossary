#include "TranslatorFactory.h"

#include "DefaultTranslatorFactory.h"

namespace glossary::translator
{
std::unique_ptr<TranslatorFactory> TranslatorFactory::createTranslatorFactory(
    const std::shared_ptr<const webConnection::HttpHandler>& httpHandler)
{
    return std::make_unique<DefaultTranslatorFactory>(httpHandler);
}
}