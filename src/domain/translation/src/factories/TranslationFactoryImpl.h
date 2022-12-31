#pragma once

#include <memory>

#include "../clients/GoogleTranslateClient.h"
#include "../repositories/TranslationRepository.h"
#include "factories/TranslationFactory.h"
#include "fileSystem/FileAccess.h"
#include "httpClient/HttpClient.h"
#include "queries/GetSupportedLanguagesQuery.h"
#include "queries/GetTranslationQuery.h"
#include "TranslationConfig.h"

namespace glossary::translation
{
class DictionaryFactoryImpl : public DictionaryFactory
{
public:
    DictionaryFactoryImpl(const std::shared_ptr<common::fileSystem::FileAccess>&,
                          const std::shared_ptr<common::httpClient::HttpClient>&, const TranslationConfig&);

    std::unique_ptr<GetSupportedLanguagesQuery> createGetSupportedLanguagesQuery() const override;
    std::unique_ptr<GetTranslationQuery> createGetTranslationQuery() const override;

private:
    std::shared_ptr<GoogleTranslateClient> googleTranslateClient;
    std::shared_ptr<TranslationRepository> translationRepository;
};
}
