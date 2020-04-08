#include "GlossaryApplicationFactory.h"

#include "DefaultAnswerValidator.h"
#include "DefaultDictionarySynchronizer.h"
#include "DefaultWordDescriptionRetrieverService.h"
#include "GlossaryApplication.h"
#include "TranslationConcurrentLoader.h"
#include "UserStandardInputPrompt.h"
#include "WordDescriptionConcurrentLoader.h"
#include "dictionaryService/DictionaryServiceFactory.h"
#include "statisticsRepository/StatisticsRepositoryFactory.h"
#include "translationRepository/TranslationRepositoryFactory.h"
#include "translationService/TranslationServiceFactory.h"
#include "translator/TranslatorFactory.h"
#include "utils/FileAccessFactory.h"
#include "webConnection/HttpHandlerFactory.h"
#include "wordDescriptionDownloader/WordDescriptionDownloaderFactory.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryFactory.h"

namespace glossary
{
namespace
{
std::shared_ptr<utils::FileAccess> createFileAccess();
std::shared_ptr<const webConnection::HttpHandler> createHttpHandler();
std::shared_ptr<dictionaryService::DictionaryService>
createDictionaryService(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<translator::Translator>
createTranslator(const std::shared_ptr<const webConnection::HttpHandler>&);
std::shared_ptr<translationRepository::TranslationRepository>
createTranslationRepository(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<translationService::TranslationRetrieverService>
createTranslationRetrieverService(const std::shared_ptr<translator::Translator>&,
                                  const std::shared_ptr<translationRepository::TranslationRepository>&);
std::shared_ptr<statisticsRepository::StatisticsRepository>
createStatisticsRepository(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>
createWordDescriptionDownloader(const std::shared_ptr<const webConnection::HttpHandler>&);
std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>
createWordDescriptionRepository(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<WordDescriptionRetrieverService> createWordDescriptionRetrieverService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&);
std::shared_ptr<WordDescriptionLoader>
createWordDescriptionLoader(const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
                            const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&);
std::shared_ptr<TranslationLoader>
createTranslationLoader(const std::shared_ptr<translator::Translator>&,
                        const std::shared_ptr<translationRepository::TranslationRepository>&);
std::shared_ptr<DictionarySynchronizer>
createDictionarySynchronizer(const std::shared_ptr<dictionaryService::DictionaryService>&,
                             const std::shared_ptr<WordDescriptionLoader>&,
                             const std::shared_ptr<TranslationLoader>&);
std::unique_ptr<AnswerValidator> createAnswerValidator();
std::unique_ptr<UserPrompt> createUserPrompt();
}

std::unique_ptr<Application> GlossaryApplicationFactory::createApplication() const
{
    auto fileAccess = createFileAccess();
    auto httpHandler = createHttpHandler();

    auto dictionaryService = createDictionaryService(fileAccess);

    auto translator = createTranslator(httpHandler);
    auto translationRepository = createTranslationRepository(fileAccess);
    auto translationRetrieverService = createTranslationRetrieverService(translator, translationRepository);

    auto statisticsRepository = createStatisticsRepository(fileAccess);

    auto wordDescriptionDownloader = createWordDescriptionDownloader(httpHandler);
    auto wordDescriptionRepository = createWordDescriptionRepository(fileAccess);
    auto wordDescriptionRetrieverService =
        createWordDescriptionRetrieverService(wordDescriptionDownloader, wordDescriptionRepository);

    auto wordDescriptionLoader =
        createWordDescriptionLoader(wordDescriptionDownloader, wordDescriptionRepository);
    auto translationLoader = createTranslationLoader(translator, translationRepository);
    auto dictionarySynchronizer =
        createDictionarySynchronizer(dictionaryService, wordDescriptionLoader, translationLoader);

    auto answerValidator = createAnswerValidator();
    auto userPrompt = createUserPrompt();

    return std::make_unique<GlossaryApplication>(
        dictionaryService, translationRetrieverService, statisticsRepository, wordDescriptionRetrieverService,
        dictionarySynchronizer, std::move(answerValidator), std::move(userPrompt));
}

namespace
{
std::shared_ptr<utils::FileAccess> createFileAccess()
{
    return utils::FileAccessFactory::createFileAccessFactory()->createDefaultFileAccess();
}

std::shared_ptr<const webConnection::HttpHandler> createHttpHandler()
{
    auto httpHandlerFactory = webConnection::HttpHandlerFactory::createHttpHandlerFactory();
    return httpHandlerFactory->createHttpHandler();
}

std::shared_ptr<dictionaryService::DictionaryService>
createDictionaryService(const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    auto dictionaryServiceFactory =
        dictionaryService::DictionaryServiceFactory::createDictionaryServiceFactory(fileAccess);
    return dictionaryServiceFactory->createDictionaryService();
}

std::shared_ptr<translator::Translator>
createTranslator(const std::shared_ptr<const webConnection::HttpHandler>& httpHandler)
{
    auto translatorFactory = translator::TranslatorFactory::createTranslatorFactory(httpHandler);
    return translatorFactory->createTranslator();
}

std::shared_ptr<translationRepository::TranslationRepository>
createTranslationRepository(const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    auto translationRepositoryFactory =
        translationRepository::TranslationRepositoryFactory::createTranslationRepositoryFactory(fileAccess);
    return translationRepositoryFactory->createTranslationRepository();
}

std::shared_ptr<translationService::TranslationRetrieverService> createTranslationRetrieverService(
    const std::shared_ptr<translator::Translator>& translator,
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository)
{
    auto translationServiceFactory =
        translationService::TranslationServiceFactory::createTranslationServiceFactory();
    return translationServiceFactory->createTranslationService(translator, translationRepository);
}

std::shared_ptr<statisticsRepository::StatisticsRepository>
createStatisticsRepository(const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    auto statisticsRepositoryFactory =
        statisticsRepository::StatisticsRepositoryFactory::createStatisticsRepositoryFactory(fileAccess);
    return statisticsRepositoryFactory->createStatisticsRepository();
}

std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>
createWordDescriptionDownloader(const std::shared_ptr<const webConnection::HttpHandler>& httpHandler)
{
    auto wordDescriptionDownloaderFactory =
        wordDescriptionDownloader::WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(
            httpHandler);
    return wordDescriptionDownloaderFactory->createWordDescriptionDownloader();
}

std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>
createWordDescriptionRepository(const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    auto wordDescriptionRepositoryFactory =
        wordDescriptionRepository::WordDescriptionRepositoryFactory::createWordDescriptionRepositoryFactory(
            fileAccess);
    return wordDescriptionRepositoryFactory->createWordDescriptionRepository();
}

std::shared_ptr<WordDescriptionRetrieverService> createWordDescriptionRetrieverService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>& wordDescriptionDownloader,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>& wordDescriptionRepository)
{
    return std::make_shared<DefaultWordDescriptionRetrieverService>(wordDescriptionDownloader,
                                                                    wordDescriptionRepository);
}

std::shared_ptr<WordDescriptionLoader> createWordDescriptionLoader(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>& wordDescriptionDownloader,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>& wordDescriptionRepository)
{
    return std::make_shared<WordDescriptionConcurrentLoader>(wordDescriptionDownloader,
                                                             wordDescriptionRepository);
}

std::shared_ptr<TranslationLoader> createTranslationLoader(
    const std::shared_ptr<translator::Translator>& translator,
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository)
{
    return std::make_shared<TranslationConcurrentLoader>(translator, translationRepository);
}

std::shared_ptr<DictionarySynchronizer>
createDictionarySynchronizer(const std::shared_ptr<dictionaryService::DictionaryService>& dictionaryService,
                             const std::shared_ptr<WordDescriptionLoader>& wordDescriptionLoader,
                             const std::shared_ptr<TranslationLoader>& translationLoader)
{
    return std::make_shared<DefaultDictionarySynchronizer>(dictionaryService, wordDescriptionLoader,
                                                           translationLoader);
}

std::unique_ptr<AnswerValidator> createAnswerValidator()
{
    return std::make_unique<DefaultAnswerValidator>();
}

std::unique_ptr<UserPrompt> createUserPrompt()
{
    return std::make_unique<UserStandardInputPrompt>();
}

}
}