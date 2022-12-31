#include "DictionaryFactoryImpl.h"

#include <utility>

#include "../clients/WordsApiClientImpl.h"
#include "../commands/AddWordToDictionaryCommandImpl.h"
#include "../commands/CreateDictionaryCommandImpl.h"
#include "../commands/CreateDictionaryFromCsvFileCommandImpl.h"
#include "../commands/RemoveDictionaryCommandImpl.h"
#include "../commands/RemoveWordFromDictionaryCommandImpl.h"
#include "../commands/UpdateWordTranslationInDictionaryCommandImpl.h"
#include "../queries/GetDictionariesEnglishWordsQueryImpl.h"
#include "../queries/GetDictionariesNamesQueryImpl.h"
#include "../queries/GetDictionariesQueryImpl.h"
#include "../queries/GetDictionaryEnglishWordsQueryImpl.h"
#include "../queries/GetDictionaryQueryImpl.h"
#include "../queries/GetRandomWordFromDictionariesQueryImpl.h"
#include "../queries/GetRandomWordFromDictionaryQueryImpl.h"
#include "../queries/GetWordDescriptionQueryImpl.h"
#include "../readers/DictionaryWordsCsvReaderImpl.h"
#include "../repositories/DefaultDictionaryRepository.h"
#include "../repositories/DefaultWordDescriptionRepository.h"
#include "../repositories/DictionaryPersistentStorage.h"
#include "../repositories/WordsDescriptionsPersistentStorage.h"
#include "../serializers/DictionaryJsonSerializer.h"
#include "../serializers/WordsDescriptionsJsonSerializer.h"

namespace glossary::dictionary
{
DictionaryFactoryImpl::DictionaryFactoryImpl(
    const std::shared_ptr<common::fileSystem::FileAccess>& fileAccessInit,
    std::shared_ptr<common::httpClient::HttpClient> httpClientInit,
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGeneratorInit,
    const DictionaryConfig& configInit)
    : fileAccess{fileAccessInit},
      httpClient{std::move(httpClientInit)},
      dictionaryRepository{std::make_shared<DefaultDictionaryRepository>(
          std::make_unique<DictionaryPersistentStorage>(fileAccessInit, std::make_shared<DictionaryJsonSerializer>()))},
      wordDescriptionRepository{
          std::make_shared<DefaultWordDescriptionRepository>(std::make_unique<WordsDescriptionsPersistentStorage>(
              fileAccessInit, std::make_shared<WordsDescriptionsJsonSerializer>()))},
      randomNumberGenerator{std::move(randomNumberGeneratorInit)},
      config{configInit}
{
}

std::unique_ptr<AddWordToDictionaryCommand> DictionaryFactoryImpl::createAddWordToDictionaryCommand() const
{
    return std::make_unique<AddWordToDictionaryCommandImpl>(dictionaryRepository);
}

std::unique_ptr<CreateDictionaryCommand> DictionaryFactoryImpl::createCreateDictionaryCommand() const
{
    return std::make_unique<CreateDictionaryCommandImpl>(dictionaryRepository);
}

std::unique_ptr<CreateDictionaryFromCsvFileCommand>
DictionaryFactoryImpl::createCreateDictionaryFromCsvFileCommand() const
{
    return std::make_unique<CreateDictionaryFromCsvFileCommandImpl>(
        dictionaryRepository, std::make_unique<DictionaryWordsCsvReaderImpl>(fileAccess));
}

std::unique_ptr<RemoveDictionaryCommand> DictionaryFactoryImpl::createRemoveDictionaryCommand() const
{
    return std::make_unique<RemoveDictionaryCommandImpl>(dictionaryRepository);
}

std::unique_ptr<RemoveWordFromDictionaryCommand> DictionaryFactoryImpl::createRemoveWordFromDictionaryCommand() const
{
    return std::make_unique<RemoveWordFromDictionaryCommandImpl>(dictionaryRepository);
}

std::unique_ptr<UpdateWordTranslationInDictionaryCommand>
DictionaryFactoryImpl::createUpdateWordTranslationInDictionaryCommand() const
{
    return std::make_unique<UpdateWordTranslationInDictionaryCommandImpl>(dictionaryRepository);
}

std::unique_ptr<GetDictionariesEnglishWordsQuery> DictionaryFactoryImpl::createGetDictionariesEnglishWordsQuery() const
{
    return std::make_unique<GetDictionariesEnglishWordsQueryImpl>(dictionaryRepository);
}

std::unique_ptr<GetDictionariesNamesQuery> DictionaryFactoryImpl::createGetDictionariesNamesQuery() const
{
    return std::make_unique<GetDictionariesNamesQueryImpl>(dictionaryRepository);
}

std::unique_ptr<GetDictionariesQuery> DictionaryFactoryImpl::createGetDictionariesQuery() const
{
    return std::make_unique<GetDictionariesQueryImpl>(dictionaryRepository);
}

std::unique_ptr<GetDictionaryEnglishWordsQuery> DictionaryFactoryImpl::createGetDictionaryEnglishWordsQuery() const
{
    return std::make_unique<GetDictionaryEnglishWordsQueryImpl>(dictionaryRepository);
}

std::unique_ptr<GetDictionaryQuery> DictionaryFactoryImpl::createGetDictionaryQuery() const
{
    return std::make_unique<GetDictionaryQueryImpl>(dictionaryRepository);
}

std::unique_ptr<GetRandomWordFromDictionariesQuery>
DictionaryFactoryImpl::createGetRandomWordFromDictionariesQuery() const
{
    return std::make_unique<GetRandomWordFromDictionariesQueryImpl>(dictionaryRepository, randomNumberGenerator);
}

std::unique_ptr<GetRandomWordFromDictionaryQuery> DictionaryFactoryImpl::createGetRandomWordFromDictionaryQuery() const
{
    return std::make_unique<GetRandomWordFromDictionaryQueryImpl>(dictionaryRepository, randomNumberGenerator);
}

std::unique_ptr<GetWordDescriptionQuery> DictionaryFactoryImpl::createGetWordDescriptionQuery() const
{
    return std::make_unique<GetWordDescriptionQueryImpl>(
        wordDescriptionRepository,
        std::make_unique<WordsApiClientImpl>(
            httpClient, WordsApiClientConfig{config.wordsApiBaseUrl, config.wordsApiHost, config.wordsApiKey}));
}

}
