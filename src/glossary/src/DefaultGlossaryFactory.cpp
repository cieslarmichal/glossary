#include "DefaultGlossaryFactory.h"

#include "fmt/core.h"

#include "DefaultDictionaryStatisticsCounter.h"
#include "DefaultGlossary.h"
#include "dictionary/DictionaryConfig.h"
#include "dictionary/factories/DictionaryFactory.h"
#include "dotenv.h"
#include "fileSystem/FileAccessFactory.h"
#include "fileSystem/GetProjectPath.h"
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
    const auto rootDirectory = common::fileSystem::getProjectPath("glossary");

    const auto envFilePath = fmt::format("{}{}", rootDirectory, ".env");

    dotenv::env.load_dotenv(envFilePath, true);

    std::shared_ptr<common::fileSystem::FileAccess> fileAccess =
        common::fileSystem::FileAccessFactory::createFileAccessFactory()->createDefaultFileAccess();

    std::shared_ptr<common::httpClient::HttpClient> httpClient =
        common::httpClient::HttpClientFactory::createHttpClientFactory()->createHttpClient();

    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGenerator =
        common::random::RandomNumberGeneratorFactory::createRandomNumberGenerator();

    const std::string wordsApiBaseUrl = std::getenv("WORDS_API_BASE_URL");
    const std::string wordsApiHost= std::getenv("WORDS_API_HOST");
    const std::string wordsApiKey = std::getenv("WORDS_API_KEY");

    auto dictionaryConfig = dictionary::DictionaryConfig{wordsApiBaseUrl, wordsApiHost, wordsApiKey};

    auto dictionaryFactory = dictionary::DictionaryFactory::createDictionaryFactory(
        fileAccess, httpClient, randomNumberGenerator, dictionaryConfig);

    auto statisticsFactory = statistics::StatisticsFactory::createStatisticsFactory(fileAccess);

    const std::string googleTranslateBaseUrl = std::getenv("GOOGLE_TRANSLATE_BASE_URL");
    const std::string googleTranslateApiKey = std::getenv("GOOGLE_TRANSLATE_API_KEY");

    auto translationConfig = translation::TranslationConfig{googleTranslateBaseUrl, googleTranslateApiKey};

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
    std::shared_ptr<dictionary::GetWordDescriptionQuery> getWordDescriptionQuery =
        dictionaryFactory->createGetWordDescriptionQuery();

    auto addCorrectAnswerCommand = statisticsFactory->createAddCorrectAnswerCommand();
    auto addIncorrectAnswerCommand = statisticsFactory->createAddIncorrectAnswerCommand();
    auto addWordStatisticsCommand = statisticsFactory->createAddWordStatisticsCommand();
    auto resetWordsStatisticsCommand = statisticsFactory->createResetWordsStatisticsCommand();
    auto getWordsStatisticsQuery = statisticsFactory->createGetWordsStatisticsQuery();

    std::shared_ptr<translation::GetTranslationQuery> getTranslationQuery =
        translationFactory->createGetTranslationQuery();
    auto getSupportedLanguagesQuery = translationFactory->createGetSupportedLanguagesQuery();

    auto translationUpdater = std::make_unique<TranslationConcurrentUpdater>(getTranslationQuery);

    auto wordDescriptionUpdater = std::make_unique<WordDescriptionConcurrentUpdater>(getWordDescriptionQuery);

    return std::make_unique<DefaultGlossary>(
        std::move(dictionaryStatisticsCounter), std::move(addWordToDictionaryCommand),
        std::move(createDictionaryCommand), std::move(removeDictionaryCommand),
        std::move(createDictionaryFromCsvFileCommand), std::move(removeWordFromDictionaryCommand),
        std::move(updateWordTranslationInDictionaryCommand), std::move(getDictionariesEnglishWordsQuery),
        std::move(getDictionariesNamesQuery), std::move(getDictionariesQuery),
        std::move(getDictionaryEnglishWordsQuery), std::move(getDictionaryQuery),
        std::move(getRandomWordFromDictionariesQuery), std::move(getRandomWordFromDictionaryQuery),
        getWordDescriptionQuery, std::move(addCorrectAnswerCommand), std::move(addIncorrectAnswerCommand),
        std::move(addWordStatisticsCommand), std::move(resetWordsStatisticsCommand), std::move(getWordsStatisticsQuery),
        getTranslationQuery, std::move(getSupportedLanguagesQuery), std::move(translationUpdater),
        std::move(wordDescriptionUpdater));
}
}
