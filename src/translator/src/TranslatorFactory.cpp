#include "TranslatorFactory.h"

#include "TranslatorFactoryImpl.h"

namespace translator
{

std::unique_ptr<TranslatorFactory> TranslatorFactory::createTranslatorFactory(
    const std::shared_ptr<webConnection::HttpHandler>& httpHandler)
{
    return std::make_unique<TranslatorFactoryImpl>(httpHandler);
}
}