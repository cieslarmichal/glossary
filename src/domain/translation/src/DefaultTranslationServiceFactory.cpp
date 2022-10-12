#include "DefaultTranslationServiceFactory.h"

#include "DefaultTranslationService.h"
#include "GoogleTranslateApiJsonResponseDeserializer.h"

namespace glossary::translation
{
DefaultTranslationServiceFactory::DefaultTranslationServiceFactory(
    std::shared_ptr<const httpClient::HttpClient> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

std::unique_ptr<TranslationService> DefaultTranslationServiceFactory::createTranslator() const
{
    return std::make_unique<DefaultTranslationService>(
        httpHandler, std::make_unique<GoogleTranslateApiJsonResponseDeserializer>());
}

}