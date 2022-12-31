#include "DefaultGlossaryFactory.h"

#include "DefaultDictionaryStatisticsCounter.h"
#include "DefaultGlossary.h"
#include "dictionary/DictionaryConfig.h"
#include "dictionary/factories/DictionaryFactory.h"
#include "fileSystem/FileAccessFactory.h"
#include "httpClient/HttpClientFactory.h"
#include "random/RandomNumberGeneratorFactory.h"
#include "statistics/factories/StatisticsFactory.h"
#include "translation/factories/TranslationFactory.h"
#include "translation/TranslationConfig.h"
#include "TranslationConcurrentUpdater.h"
#include "WordDescriptionConcurrentUpdater.h"

namespace glossary
{
std::unique_ptr<Glossary> DefaultGlossaryFactory::createGlossary() const
{
    std::shared_ptr<common::fileSystem::FileAccess> fileAccess =
        common::fileSystem::FileAccessFactory::createFileAccessFactory()->createDefaultFileAccess();

    std::shared_ptr<common::httpClient::HttpClient> httpClient =
        common::httpClient::HttpClientFactory::createHttpClientFactory()->createHttpClient();

    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGenerator =
        common::random::RandomNumberGeneratorFactory::createRandomNumberGenerator();

    auto dictionaryConfig = dictionary::DictionaryConfig{"TODO", "", ""};
    auto dictionaryFactory = dictionary::DictionaryFactory::createDictionaryFactory(
        fileAccess, httpClient, randomNumberGenerator, dictionaryConfig);

    auto statisticsFactory = statistics::StatisticsFactory::createStatisticsFactory(fileAccess);

    auto translationConfig = translation::TranslationConfig{"TODO", ""};
    auto translationFactory =
        translation::TranslationFactory::createTranslationFactory(fileAccess, httpClient, translationConfig);

    auto dictionaryStatisticsCounter = std::make_unique<DefaultDictionaryStatisticsCounter>();

    auto addWordToDictionaryCommand = dictionaryFactory->createAddWordToDictionaryCommand();
    auto createDictionaryCommand = dictionaryFactory->createCreateDictionaryCommand();
    auto removeDictionaryCommand = dictionaryFactory->createRemoveDictionaryCommand();
    auto createDictionaryFromCsvFileCommand = dictionaryFactory->createCreateDictionaryFromCsvFileCommand();
    auto removeWordFromDictionaryCommand = dictionaryFactory->createRemoveWordFromDictionaryCommand();
    auto updateWordTranslationInDictionaryCommand = dictionaryFactory->createUpdateWordTranslationInDictionaryCommand();
    auto getDictionariesEnglishWordsQuery = dictionaryFactory->createGetDictionariesEnglishWordsQuery();
    auto getDictionariesNamesQuery = dictionaryFactory->createGetDictionariesNamesQuery();
    auto getDictionariesQuery = dictionaryFactory->createGetDictionariesQuery();
    auto getDictionaryEnglishWordsQuery = dictionaryFactory->createGetDictionaryEnglishWordsQuery();
    auto getDictionaryQuery = dictionaryFactory->createGetDictionaryQuery();
    auto getRandomWordFromDictionariesQuery = dictionaryFactory->createGetRandomWordFromDictionariesQuery();
    auto getRandomWordFromDictionaryQuery = dictionaryFactory->createGetRandomWordFromDictionaryQuery();
    auto getWordDescriptionQuery = dictionaryFactory->createGetWordDescriptionQuery();

    auto addCorrectAnswerCommand = statisticsFactory->createAddCorrectAnswerCommand();
    auto addIncorrectAnswerCommand = statisticsFactory->createAddIncorrectAnswerCommand();
    auto addWordStatisticsCommand = statisticsFactory->createAddWordStatisticsCommand();
    auto resetWordsStatisticsCommand = statisticsFactory->createResetWordsStatisticsCommand();
    auto getWordsStatisticsQuery = statisticsFactory->createGetWordsStatisticsQuery();

    auto getTranslationQuery = translationFactory->createGetTranslationQuery();
    auto getSupportedLanguagesQuery = translationFactory->createGetSupportedLanguagesQuery();

    //    auto dictionaryTranslationUpdater = createDictionaryTranslationUpdater(dictionaryService, translationService);
    //
    //    auto wordDescriptionUpdater = createWordDescriptionUpdater(wordDescriptionService, wordDescriptionRepository);
    //    auto translationUpdater = createTranslationUpdater(translationService, translationRepository);
    //    std::vector<std::shared_ptr<dictionary::DictionaryObserver>> observers{wordDescriptionUpdater,
    //    translationUpdater};

    return std::make_unique<DefaultGlossary>(
        dictionaryStatisticsCounter, addWordToDictionaryCommand, createDictionaryCommand, removeDictionaryCommand,
        createDictionaryFromCsvFileCommand, removeWordFromDictionaryCommand, updateWordTranslationInDictionaryCommand,
        getDictionariesEnglishWordsQuery, getDictionariesNamesQuery, getDictionariesQuery,
        getDictionaryEnglishWordsQuery, getDictionaryQuery, getRandomWordFromDictionariesQuery,
        getRandomWordFromDictionaryQuery, getWordDescriptionQuery, addCorrectAnswerCommand, addIncorrectAnswerCommand,
        addWordStatisticsCommand, resetWordsStatisticsCommand, getWordsStatisticsQuery, getTranslationQuery,
        getSupportedLanguagesQuery);
}
}
