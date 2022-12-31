#include "factories/TranslationFactory.h"

#include "TranslationFactoryImpl.h"

namespace glossary::translation
{
std::unique_ptr<TranslationFactory>
TranslationFactory::createTranslationFactory(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess,
                                             const std::shared_ptr<common::httpClient::HttpClient>& httpClient,
                                             const TranslationConfig& config)
{
    return std::make_unique<TranslationFactoryImpl>(fileAccess, httpClient, config);
}
}
