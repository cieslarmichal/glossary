#include "factories/DictionaryFactory.h"

#include "DictionaryFactoryImpl.h"

namespace glossary::dictionary
{
std::unique_ptr<DictionaryFactory> DictionaryFactory::createDictionaryFactory(
    const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess,
    const std::shared_ptr<common::httpClient::HttpClient>& httpClient,
    const std::shared_ptr<common::random::RandomNumberGenerator>& randomNumberGenerator, const DictionaryConfig& config)
{
    return std::make_unique<DictionaryFactoryImpl>(fileAccess, httpClient, randomNumberGenerator, config);
}
}
