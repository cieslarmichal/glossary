#include "TranslatorFactory.h"

#include "DefaultTranslationServiceFactory.h"

namespace glossary::translation
{
std::unique_ptr<TranslatorFactory>
TranslatorFactory::createTranslatorFactory(const std::shared_ptr<const httpClient::HttpClient>& httpHandler)
{
    return std::make_unique<DefaultTranslationServiceFactory>(httpHandler);
}
}