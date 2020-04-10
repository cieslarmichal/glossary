#include "DefaultGlossaryFactory.h"

#include "DefaultAnswerValidator.h"
#include "DefaultDictionarySynchronizer.h"
#include "DefaultDictionaryTranslationUpdater.h"
#include "DefaultGlossary.h"
#include "MerriamWebsterConnectionChecker.h"
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
#include "wordDescriptionService/WordDescriptionServiceFactory.h"

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
                                  const std::shared_ptr<translationRepository::TranslationRepository>&,
                                  const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<statisticsRepository::StatisticsRepository>
createStatisticsRepository(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>
createWordDescriptionDownloader(const std::shared_ptr<const webConnection::HttpHandler>&);
std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>
createWordDescriptionRepository(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>
createWordDescriptionRetrieverService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&);
std::shared_ptr<WordDescriptionLoader>
createWordDescriptionLoader(const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
                            const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&);
std::shared_ptr<TranslationLoader>
createTranslationLoader(const std::shared_ptr<translationService::TranslationRetrieverService>&,
                        const std::shared_ptr<translationRepository::TranslationRepository>&);
std::shared_ptr<DictionarySynchronizer>
createDictionarySynchronizer(const std::shared_ptr<dictionaryService::DictionaryService>&,
                             const std::shared_ptr<WordDescriptionLoader>&,
                             const std::shared_ptr<TranslationLoader>&);
std::shared_ptr<DictionaryTranslationUpdater>
createDictionaryTranslationUpdater(const std::shared_ptr<dictionaryService::DictionaryService>&,
                                   const std::shared_ptr<translationService::TranslationRetrieverService>&);
std::unique_ptr<ConnectionChecker>
createConnectionChecker(const std::shared_ptr<const webConnection::HttpHandler>&);
std::unique_ptr<AnswerValidator> createAnswerValidator();
std::unique_ptr<UserPrompt> createUserPrompt();
}

std::unique_ptr<Glossary> DefaultGlossaryFactory::createGlossary() const
{
    auto fileAccess = createFileAccess();
    auto httpHandler = createHttpHandler();

    auto dictionaryService = createDictionaryService(fileAccess);

    auto translator = createTranslator(httpHandler);
    auto translationRepository = createTranslationRepository(fileAccess);
    auto translationRetrieverService =
        createTranslationRetrieverService(translator, translationRepository, fileAccess);

    auto statisticsRepository = createStatisticsRepository(fileAccess);

    auto wordDescriptionDownloader = createWordDescriptionDownloader(httpHandler);
    auto wordDescriptionRepository = createWordDescriptionRepository(fileAccess);
    auto wordDescriptionRetrieverService =
        createWordDescriptionRetrieverService(wordDescriptionDownloader, wordDescriptionRepository);

    auto wordDescriptionLoader =
        createWordDescriptionLoader(wordDescriptionDownloader, wordDescriptionRepository);
    auto translationLoader = createTranslationLoader(translationRetrieverService, translationRepository);
    auto dictionarySynchronizer =
        createDictionarySynchronizer(dictionaryService, wordDescriptionLoader, translationLoader);

    auto dictionaryTranslationUpdater =
        createDictionaryTranslationUpdater(dictionaryService, translationRetrieverService);

    auto connectionChecker = createConnectionChecker(httpHandler);
    auto answerValidator = createAnswerValidator();
    auto userPrompt = createUserPrompt();

    return std::make_unique<DefaultGlossary>(
        dictionaryService, translationRetrieverService, statisticsRepository, wordDescriptionRetrieverService,
        dictionarySynchronizer, dictionaryTranslationUpdater, std::move(connectionChecker),
        std::move(answerValidator), std::move(userPrompt));
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
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository,
    const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    auto translationServiceFactory =
        translationService::TranslationServiceFactory::createTranslationServiceFactory(fileAccess);
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

std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>
createWordDescriptionRetrieverService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>& wordDescriptionDownloader,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>& wordDescriptionRepository)
{
    auto wordDescriptionServiceFactory =
        wordDescriptionService::WordDescriptionServiceFactory::createWordDescriptionServiceFactory();
    return wordDescriptionServiceFactory->createWordDescriptionService(wordDescriptionDownloader,
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
    const std::shared_ptr<translationService::TranslationRetrieverService>& translationService,
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository)
{
    return std::make_shared<TranslationConcurrentLoader>(translationService, translationRepository);
}

std::shared_ptr<DictionarySynchronizer>
createDictionarySynchronizer(const std::shared_ptr<dictionaryService::DictionaryService>& dictionaryService,
                             const std::shared_ptr<WordDescriptionLoader>& wordDescriptionLoader,
                             const std::shared_ptr<TranslationLoader>& translationLoader)
{
    return std::make_shared<DefaultDictionarySynchronizer>(dictionaryService, wordDescriptionLoader,
                                                           translationLoader);
}

std::shared_ptr<DictionaryTranslationUpdater> createDictionaryTranslationUpdater(
    const std::shared_ptr<dictionaryService::DictionaryService>& dictionaryService,
    const std::shared_ptr<translationService::TranslationRetrieverService>& translationService)
{
    return std::make_shared<DefaultDictionaryTranslationUpdater>(dictionaryService, translationService);
}

std::unique_ptr<ConnectionChecker>
createConnectionChecker(const std::shared_ptr<const webConnection::HttpHandler>& httpHandler)
{
    return std::make_unique<MerriamWebsterConnectionChecker>(httpHandler);
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