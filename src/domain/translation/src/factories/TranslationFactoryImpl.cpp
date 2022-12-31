#include "TranslationFactoryImpl.h"

#include "../clients/GoogleTranslateClientImpl.h"
#include "../queries/GetSupportedLanguagesQueryImpl.h"
#include "../queries/GetTranslationQueryImpl.h"
#include "../repositories/DefaultTranslationRepository.h"
#include "../repositories/TranslationsPersistentStorage.h"
#include "../serializers/TranslationsJsonSerializer.h"
#include "factories/TranslationFactory.h"

namespace glossary::translation
{
TranslationFactoryImpl::TranslationFactoryImpl(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess,
                                               const std::shared_ptr<common::httpClient::HttpClient>& httpClient,
                                               const TranslationConfig& config)
    : googleTranslateClient{std::make_shared<GoogleTranslateClientImpl>(
          httpClient, GoogleTranslateClientConfig{config.googleTranslateBaseUrl, config.googleTranslateApiKey})},
      translationRepository{std::make_shared<DefaultTranslationRepository>(
          std::make_unique<TranslationsPersistentStorage>(fileAccess, std::make_shared<TranslationsJsonSerializer>()))}
{
}

std::unique_ptr<GetSupportedLanguagesQuery> TranslationFactoryImpl::createGetSupportedLanguagesQuery() const
{
    return std::make_unique<GetSupportedLanguagesQueryImpl>();
}

std::unique_ptr<GetTranslationQuery> TranslationFactoryImpl::createGetTranslationQuery() const
{
    return std::make_unique<GetTranslationQueryImpl>(googleTranslateClient, translationRepository);
}
}
