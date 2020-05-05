#include "DefaultDictionaryServiceFactory.h"

#include "DefaultDictionaryNamesRetriever.h"
#include "DefaultDictionaryService.h"
#include "DefaultDictionaryWordRandomizer.h"
#include "DefaultDictionaryWordsRetriever.h"
#include "DefaultRandomDictionaryWordRetriever.h"
#include "DictionaryObserverService.h"
#include "csvFileReading/DictionaryWordsCsvFileReader.h"
#include "repository/DefaultDictionaryRepository.h"
#include "repository/DictionaryPersistentStorage.h"
#include "serialization/DictionaryJsonSerializer.h"
#include "utils/RandomNumberMersenneTwisterGenerator.h"

namespace glossary::dictionaryService
{
DefaultDictionaryServiceFactory::DefaultDictionaryServiceFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<DictionaryService> DefaultDictionaryServiceFactory::createDictionaryService() const
{
    auto dictionaryRepository = std::make_shared<repository::DefaultDictionaryRepository>(
        std::make_unique<repository::DictionaryPersistentStorage>(
            fileAccess, std::make_shared<serialization::DictionaryJsonSerializer>()));

    auto dictionaryNamesRetriever = std::make_unique<DefaultDictionaryNamesRetriever>(dictionaryRepository);

    auto dictionaryWordsRetriever = std::make_unique<DefaultDictionaryWordsRetriever>(dictionaryRepository);

    auto randomDictionaryWordRetriever = std::make_unique<DefaultRandomDictionaryWordRetriever>(
        dictionaryRepository, std::make_unique<DefaultDictionaryWordRandomizer>(
                                  std::make_shared<utils::RandomNumberMersenneTwisterGenerator>()));

    auto dictionaryWordsFileReader =
        std::make_unique<csvFileReading::DictionaryWordsCsvFileReader>(fileAccess);

    auto observerService = std::make_unique<DictionaryObserverService>();

    return std::make_unique<DefaultDictionaryService>(
        std::move(dictionaryRepository), std::move(dictionaryNamesRetriever),
        std::move(dictionaryWordsRetriever), std::move(randomDictionaryWordRetriever),
        std::move(dictionaryWordsFileReader), std::move(observerService));
}
}
