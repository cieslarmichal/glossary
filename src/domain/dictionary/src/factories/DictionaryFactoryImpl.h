#pragma once

#include <memory>

#include "../clients/WordsApiClient.h"
#include "../repositories/DictionaryRepository.h"
#include "../repositories/WordDescriptionRepository.h"
#include "DictionaryConfig.h"
#include "factories/DictionaryFactory.h"
#include "fileSystem/FileAccess.h"
#include "httpClient/HttpClient.h"
#include "random/RandomNumberGenerator.h"

namespace glossary::dictionary
{
class DictionaryFactoryImpl : public DictionaryFactory
{
public:
    DictionaryFactoryImpl(const std::shared_ptr<common::fileSystem::FileAccess>&,
                          std::shared_ptr<common::httpClient::HttpClient>,
                          std::shared_ptr<common::random::RandomNumberGenerator>, const DictionaryConfig&);

    std::unique_ptr<AddWordToDictionaryCommand> createAddWordToDictionaryCommand() const override;
    std::unique_ptr<CreateDictionaryCommand> createCreateDictionaryCommand() const override;
    std::unique_ptr<CreateDictionaryFromCsvFileCommand> createCreateDictionaryFromCsvFileCommand() const override;
    std::unique_ptr<RemoveDictionaryCommand> createRemoveDictionaryCommand() const override;
    std::unique_ptr<RemoveWordFromDictionaryCommand> createRemoveWordFromDictionaryCommand() const override;
    std::unique_ptr<UpdateWordTranslationInDictionaryCommand>
    createUpdateWordTranslationInDictionaryCommand() const override;
    std::unique_ptr<GetDictionariesEnglishWordsQuery> createGetDictionariesEnglishWordsQuery() const override;
    std::unique_ptr<GetDictionariesNamesQuery> createGetDictionariesNamesQuery() const override;
    std::unique_ptr<GetDictionariesQuery> createGetDictionariesQuery() const override;
    std::unique_ptr<GetDictionaryEnglishWordsQuery> createGetDictionaryEnglishWordsQuery() const override;
    std::unique_ptr<GetDictionaryQuery> createGetDictionaryQuery() const override;
    std::unique_ptr<GetRandomWordFromDictionariesQuery> createGetRandomWordFromDictionariesQuery() const override;
    std::unique_ptr<GetRandomWordFromDictionaryQuery> createGetRandomWordFromDictionaryQuery() const override;
    std::unique_ptr<GetWordDescriptionQuery> createGetWordDescriptionQuery() const override;

private:
    std::shared_ptr<common::fileSystem::FileAccess> fileAccess;
    std::shared_ptr<common::httpClient::HttpClient> httpClient;
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::shared_ptr<WordDescriptionRepository> wordDescriptionRepository;
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGenerator;
    const DictionaryConfig& config;
};
}
