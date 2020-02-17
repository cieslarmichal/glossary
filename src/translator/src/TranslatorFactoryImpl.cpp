#include "TranslatorFactoryImpl.h"

#include "TranslationDeserializerImpl.h"
#include "TranslationRequestFormatterImpl.h"
#include "TranslatorImpl.h"

namespace translator
{

TranslatorFactoryImpl::TranslatorFactoryImpl(
    std::shared_ptr<webConnection::HttpHandler> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

std::unique_ptr<Translator> TranslatorFactoryImpl::createTranslator() const
{
    return std::make_unique<TranslatorImpl>(
        httpHandler, std::make_unique<TranslationDeserializerImpl>(),
        std::make_unique<TranslationRequestFormatterImpl>());
}

}