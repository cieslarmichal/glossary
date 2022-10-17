#include "DefaultGlossaryFactory.h"

#include "DefaultAnswerValidator.h"
#include "DefaultDictionaryStatisticsCounter.h"
#include "DefaultDictionaryTranslationUpdater.h"
#include "DefaultGlossary.h"
#include "DictionaryServiceFactory.h"
#include "ExternalServicesConnectionChecker.h"
#include "FileAccessFactory.h"
#include "StatisticsRepositoryFactory.h"
#include "TranslationConcurrentUpdater.h"
#include "TranslationRepositoryFactory.h"
#include "TranslationServiceFactory.h"
#include "TranslatorFactory.h"
#include "WordDescriptionConcurrentUpdater.h"
#include "WordDescriptionDownloaderFactory.h"
#include "WordDescriptionRepositoryFactory.h"
#include "WordDescriptionServiceFactory.h"
#include "httpClient/HttpClientFactory.h"

namespace glossary
{
namespace
{
std::shared_ptr<common::fileSystem::FileAccess> createFileAccess();
std::shared_ptr<const common::httpClient::HttpClient> createHttpHandler();
std::shared_ptr<dictionary::DictionaryService>
createDictionaryService(const std::shared_ptr<common::fileSystem::FileAccess>&);
std::shared_ptr<translation::TranslationService>
createTranslator(const std::shared_ptr<const common::httpClient::HttpClient>&);
std::shared_ptr<translation::TranslationRepository>
createTranslationRepository(const std::shared_ptr<common::fileSystem::FileAccess>&);
std::shared_ptr<translationService::TranslationService>
createTranslationService(const std::shared_ptr<translation::TranslationService>&,
                         const std::shared_ptr<translation::TranslationRepository>&,
                         const std::shared_ptr<common::fileSystem::FileAccess>&);
std::shared_ptr<statistics::StatisticsRepository>
createStatisticsRepository(const std::shared_ptr<common::fileSystem::FileAccess>&);
std::shared_ptr<dictionary::WordDescriptionDownloader>
createWordDescriptionDownloader(const std::shared_ptr<const common::httpClient::HttpClient>&);
std::shared_ptr<dictionary::WordDescriptionRepository>
createWordDescriptionRepository(const std::shared_ptr<common::fileSystem::FileAccess>&);
std::shared_ptr<wordDescriptionService::WordDescriptionService>
createWordDescriptionService(const std::shared_ptr<dictionary::WordDescriptionDownloader>&,
                             const std::shared_ptr<dictionary::WordDescriptionRepository>&,
                             const std::shared_ptr<common::fileSystem::FileAccess>&);
std::shared_ptr<dictionary::DictionaryObserver>
createWordDescriptionUpdater(const std::shared_ptr<wordDescriptionService::WordDescriptionService>&,
                             const std::shared_ptr<dictionary::WordDescriptionRepository>&);
std::shared_ptr<dictionary::DictionaryObserver>
createTranslationUpdater(const std::shared_ptr<translationService::TranslationService>&,
                         const std::shared_ptr<translation::TranslationRepository>&);
std::shared_ptr<DictionaryTranslationUpdater>
createDictionaryTranslationUpdater(const std::shared_ptr<dictionary::DictionaryService>&,
                                   const std::shared_ptr<translationService::TranslationService>&);
std::unique_ptr<DictionaryStatisticsCounter> createDictionaryStatisticsCounter();
std::unique_ptr<ConnectionChecker> createExternalServicesConnectionChecker(
    const std::shared_ptr<wordDescriptionService::WordDescriptionService>&,
    const std::shared_ptr<translationService::TranslationService>&);
std::unique_ptr<AnswerValidator> createAnswerValidator();
}

std::unique_ptr<Glossary> DefaultGlossaryFactory::createGlossary() const
{
    auto fileAccess = createFileAccess();
    auto httpHandler = createHttpHandler();

    auto dictionaryService = createDictionaryService(fileAccess);

    auto translator = createTranslator(httpHandler);
    auto translationRepository = createTranslationRepository(fileAccess);
    auto translationService = createTranslationService(translator, translationRepository, fileAccess);

    auto statisticsRepository = createStatisticsRepository(fileAccess);

    auto wordDescriptionDownloader = createWordDescriptionDownloader(httpHandler);
    auto wordDescriptionRepository = createWordDescriptionRepository(fileAccess);
    auto wordDescriptionService =
        createWordDescriptionService(wordDescriptionDownloader, wordDescriptionRepository, fileAccess);

    auto dictionaryTranslationUpdater =
        createDictionaryTranslationUpdater(dictionaryService, translationService);

    auto wordDescriptionUpdater =
        createWordDescriptionUpdater(wordDescriptionService, wordDescriptionRepository);
    auto translationUpdater = createTranslationUpdater(translationService, translationRepository);
    std::vector<std::shared_ptr<dictionary::DictionaryObserver>> observers{wordDescriptionUpdater,
                                                                           translationUpdater};

    auto dictionaryStatisticsCounter = createDictionaryStatisticsCounter();

    auto externalServicesConnectionChecker =
        createExternalServicesConnectionChecker(wordDescriptionService, translationService);
    auto answerValidator = createAnswerValidator();

    return std::make_unique<DefaultGlossary>(
        dictionaryService, translationService, statisticsRepository, wordDescriptionService,
        dictionaryTranslationUpdater, observers, std::move(dictionaryStatisticsCounter),
        std::move(externalServicesConnectionChecker), std::move(answerValidator));
}

namespace
{
std::shared_ptr<common::fileSystem::FileAccess> createFileAccess()
{
    return common::FileAccessFactory::createFileAccessFactory()->createDefaultFileAccess();
}

std::shared_ptr<const common::httpClient::HttpClient> createHttpHandler()
{
    auto httpHandlerFactory = common::httpClient::HttpClientFactory::createHttpClientFactory();
    return httpHandlerFactory->createHttpClient();
}

std::shared_ptr<dictionary::DictionaryService>
createDictionaryService(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
{
    auto dictionaryServiceFactory =
        dictionary::DictionaryServiceFactory::createDictionaryServiceFactory(fileAccess);
    return dictionaryServiceFactory->createDictionaryService();
}

std::shared_ptr<translation::TranslationService>
createTranslator(const std::shared_ptr<const common::httpClient::HttpClient>& httpHandler)
{
    auto translatorFactory = translation::TranslatorFactory::createTranslatorFactory(httpHandler);
    return translatorFactory->createTranslator();
}

std::shared_ptr<translation::TranslationRepository>
createTranslationRepository(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
{
    auto translationRepositoryFactory =
        translation::TranslationRepositoryFactory::createTranslationRepositoryFactory(fileAccess);
    return translationRepositoryFactory->createTranslationRepository();
}

std::shared_ptr<translationService::TranslationService>
createTranslationService(const std::shared_ptr<translation::TranslationService>& translator,
                         const std::shared_ptr<translation::TranslationRepository>& translationRepository,
                         const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
{
    auto translationServiceFactory =
        translationService::TranslationServiceFactory::createTranslationServiceFactory(fileAccess);
    return translationServiceFactory->createTranslationService(translator, translationRepository);
}

std::shared_ptr<statistics::StatisticsRepository>
createStatisticsRepository(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
{
    auto statisticsRepositoryFactory =
        statistics::StatisticsRepositoryFactory::createStatisticsRepositoryFactory(fileAccess);
    return statisticsRepositoryFactory->createStatisticsRepository();
}

std::shared_ptr<dictionary::WordDescriptionDownloader>
createWordDescriptionDownloader(const std::shared_ptr<const common::httpClient::HttpClient>& httpHandler)
{
    auto wordDescriptionDownloaderFactory =
        dictionary::WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(httpHandler);
    return wordDescriptionDownloaderFactory->createWordDescriptionDownloader();
}

std::shared_ptr<dictionary::WordDescriptionRepository>
createWordDescriptionRepository(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
{
    auto wordDescriptionRepositoryFactory =
        dictionary::WordDescriptionRepositoryFactory::createWordDescriptionRepositoryFactory(fileAccess);
    return wordDescriptionRepositoryFactory->createWordDescriptionRepository();
}

std::shared_ptr<wordDescriptionService::WordDescriptionService> createWordDescriptionService(
    const std::shared_ptr<dictionary::WordDescriptionDownloader>& wordDescriptionDownloader,
    const std::shared_ptr<dictionary::WordDescriptionRepository>& wordDescriptionRepository,
    const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
{
    auto wordDescriptionServiceFactory =
        wordDescriptionService::WordDescriptionServiceFactory::createWordDescriptionServiceFactory(
            fileAccess);
    return wordDescriptionServiceFactory->createWordDescriptionService(wordDescriptionDownloader,
                                                                       wordDescriptionRepository);
}

std::shared_ptr<dictionary::DictionaryObserver> createWordDescriptionUpdater(
    const std::shared_ptr<wordDescriptionService::WordDescriptionService>& wordDescriptionService,
    const std::shared_ptr<dictionary::WordDescriptionRepository>& wordDescriptionRepository)
{
    return std::make_shared<WordDescriptionConcurrentUpdater>(wordDescriptionService,
                                                              wordDescriptionRepository);
}

std::shared_ptr<dictionary::DictionaryObserver>
createTranslationUpdater(const std::shared_ptr<translationService::TranslationService>& translationService,
                         const std::shared_ptr<translation::TranslationRepository>& translationRepository)
{
    return std::make_shared<TranslationConcurrentUpdater>(translationService, translationRepository);
}

std::shared_ptr<DictionaryTranslationUpdater> createDictionaryTranslationUpdater(
    const std::shared_ptr<dictionary::DictionaryService>& dictionaryService,
    const std::shared_ptr<translationService::TranslationService>& translationService)
{
    return std::make_shared<DefaultDictionaryTranslationUpdater>(dictionaryService, translationService);
}

std::unique_ptr<DictionaryStatisticsCounter> createDictionaryStatisticsCounter()
{
    return std::make_unique<DefaultDictionaryStatisticsCounter>();
}

std::unique_ptr<ConnectionChecker> createExternalServicesConnectionChecker(
    const std::shared_ptr<wordDescriptionService::WordDescriptionService>& wordDescriptionService,
    const std::shared_ptr<translationService::TranslationService>& translationService)
{
    return std::make_unique<ExternalServicesConnectionChecker>(translationService, wordDescriptionService);
}

std::unique_ptr<AnswerValidator> createAnswerValidator()
{
    return std::make_unique<DefaultAnswerValidator>();
}

}
}