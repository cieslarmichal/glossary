#include "DefaultGlossaryFactory.h"

#include "DefaultAnswerValidator.h"
#include "DefaultDictionaryTranslationUpdater.h"
#include "DefaultGlossary.h"
#include "ExternalServicesConnectionChecker.h"
#include "TranslationConcurrentUpdater.h"
#include "WordDescriptionConcurrentUpdater.h"
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
createWordDescriptionDownloader(const std::shared_ptr<const webConnection::HttpHandler>&,
                                const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>
createWordDescriptionRepository(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>
createWordDescriptionRetrieverService(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&);
std::shared_ptr<dictionaryService::DictionaryObserver>
createWordDescriptionUpdater(const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
                             const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&);
std::shared_ptr<dictionaryService::DictionaryObserver>
createTranslationUpdater(const std::shared_ptr<translationService::TranslationRetrieverService>&,
                         const std::shared_ptr<translationRepository::TranslationRepository>&);
std::shared_ptr<DictionaryTranslationUpdater>
createDictionaryTranslationUpdater(const std::shared_ptr<dictionaryService::DictionaryService>&,
                                   const std::shared_ptr<translationService::TranslationRetrieverService>&);
std::unique_ptr<ConnectionChecker> createExternalServicesConnectionChecker(
    const std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>&,
    const std::shared_ptr<translationService::TranslationRetrieverService>&);
std::unique_ptr<AnswerValidator> createAnswerValidator();
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

    auto wordDescriptionDownloader = createWordDescriptionDownloader(httpHandler, fileAccess);
    auto wordDescriptionRepository = createWordDescriptionRepository(fileAccess);
    auto wordDescriptionRetrieverService =
        createWordDescriptionRetrieverService(wordDescriptionDownloader, wordDescriptionRepository);

    auto dictionaryTranslationUpdater =
        createDictionaryTranslationUpdater(dictionaryService, translationRetrieverService);

    auto wordDescriptionUpdater =
        createWordDescriptionUpdater(wordDescriptionDownloader, wordDescriptionRepository);
    auto translationUpdater = createTranslationUpdater(translationRetrieverService, translationRepository);
    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>> observers{wordDescriptionUpdater,
                                                                                  translationUpdater};

    auto externalServicesConnectionChecker =
        createExternalServicesConnectionChecker(wordDescriptionRetrieverService, translationRetrieverService);
    auto answerValidator = createAnswerValidator();

    return std::make_unique<DefaultGlossary>(
        dictionaryService, translationRetrieverService, statisticsRepository, wordDescriptionRetrieverService,
        dictionaryTranslationUpdater, observers, std::move(externalServicesConnectionChecker),
        std::move(answerValidator));
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
createWordDescriptionDownloader(const std::shared_ptr<const webConnection::HttpHandler>& httpHandler,
                                const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    auto wordDescriptionDownloaderFactory =
        wordDescriptionDownloader::WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(
            httpHandler, fileAccess);
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

std::shared_ptr<dictionaryService::DictionaryObserver> createWordDescriptionUpdater(
    const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>& wordDescriptionDownloader,
    const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>& wordDescriptionRepository)
{
    return std::make_shared<WordDescriptionConcurrentUpdater>(wordDescriptionDownloader,
                                                              wordDescriptionRepository);
}

std::shared_ptr<dictionaryService::DictionaryObserver> createTranslationUpdater(
    const std::shared_ptr<translationService::TranslationRetrieverService>& translationService,
    const std::shared_ptr<translationRepository::TranslationRepository>& translationRepository)
{
    return std::make_shared<TranslationConcurrentUpdater>(translationService, translationRepository);
}

std::shared_ptr<DictionaryTranslationUpdater> createDictionaryTranslationUpdater(
    const std::shared_ptr<dictionaryService::DictionaryService>& dictionaryService,
    const std::shared_ptr<translationService::TranslationRetrieverService>& translationService)
{
    return std::make_shared<DefaultDictionaryTranslationUpdater>(dictionaryService, translationService);
}

std::unique_ptr<ConnectionChecker> createExternalServicesConnectionChecker(
    const std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>& wordDescriptionService,
    const std::shared_ptr<translationService::TranslationRetrieverService>& translationService)
{
    return std::make_unique<ExternalServicesConnectionChecker>(translationService, wordDescriptionService);
}

std::unique_ptr<AnswerValidator> createAnswerValidator()
{
    return std::make_unique<DefaultAnswerValidator>();
}

}
}