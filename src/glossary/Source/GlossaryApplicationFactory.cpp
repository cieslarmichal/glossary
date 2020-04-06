#include "GlossaryApplicationFactory.h"

#include "DefaultTranslationRetrieverService.h"
#include "DefaultWordDescriptionRetrieverService.h"
#include "GlossaryApplication.h"
#include "WordDescriptionConcurrentGenerator.h"
#include "dictionaryService/DictionaryServiceFactory.h"
#include "statisticsRepository/StatisticsRepositoryFactory.h"
#include "translationRepository/TranslationRepositoryFactory.h"
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
std::shared_ptr<TranslationRetrieverService>
createTranslationRetrieverService(const std::shared_ptr<utils::FileAccess>&,
                                  const std::shared_ptr<const webConnection::HttpHandler>&);
std::shared_ptr<statisticsRepository::StatisticsRepository>
createStatisticsRepository(const std::shared_ptr<utils::FileAccess>&);
std::shared_ptr<WordDescriptionRetrieverService>
createWordDescriptionRetrieverService(const std::shared_ptr<utils::FileAccess>&,
                                      const std::shared_ptr<const webConnection::HttpHandler>&);
std::shared_ptr<WordDescriptionGenerator>
createWordDescriptionGenerator(const std::shared_ptr<WordDescriptionRetrieverService>&);
}

std::unique_ptr<Application> GlossaryApplicationFactory::createApplication() const
{
    auto fileAccess = createFileAccess();
    auto httpHandler = createHttpHandler();

    auto dictionaryService = createDictionaryService(fileAccess);
    auto translationRetrieverService = createTranslationRetrieverService(fileAccess, httpHandler);
    auto statisticsRepository = createStatisticsRepository(fileAccess);
    auto wordDescriptionRetrieverService = createWordDescriptionRetrieverService(fileAccess, httpHandler);
    auto wordDescriptionGenerator = createWordDescriptionGenerator(wordDescriptionRetrieverService);

    return std::make_unique<GlossaryApplication>(dictionaryService, translationRetrieverService,
                                                 statisticsRepository, wordDescriptionRetrieverService,
                                                 wordDescriptionGenerator);
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

std::shared_ptr<TranslationRetrieverService>
createTranslationRetrieverService(const std::shared_ptr<utils::FileAccess>& fileAccess,
                                  const std::shared_ptr<const webConnection::HttpHandler>& httpHandler)
{
    auto translationRepositoryFactory =
        translationRepository::TranslationRepositoryFactory::createTranslationRepositoryFactory(fileAccess);

    auto translatorFactory = translator::TranslatorFactory::createTranslatorFactory(httpHandler);

    return std::make_shared<DefaultTranslationRetrieverService>(
        translatorFactory->createTranslator(), translationRepositoryFactory->createTranslationRepository());
}

std::shared_ptr<statisticsRepository::StatisticsRepository>
createStatisticsRepository(const std::shared_ptr<utils::FileAccess>& fileAccess)
{
    auto statisticsRepositoryFactory =
        statisticsRepository::StatisticsRepositoryFactory::createStatisticsRepositoryFactory(fileAccess);
    return statisticsRepositoryFactory->createStatisticsRepository();
}

std::shared_ptr<WordDescriptionRetrieverService>
createWordDescriptionRetrieverService(const std::shared_ptr<utils::FileAccess>& fileAccess,
                                      const std::shared_ptr<const webConnection::HttpHandler>& httpHandler)
{
    auto wordDescriptionDownloaderFactory =
        wordDescriptionDownloader::WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(
            httpHandler);

    auto wordDescriptionRepositoryFactory =
        wordDescriptionRepository::WordDescriptionRepositoryFactory::createWordDescriptionRepositoryFactory(
            fileAccess);

    return std::make_shared<DefaultWordDescriptionRetrieverService>(
        wordDescriptionDownloaderFactory->createWordDescriptionDownloader(),
        wordDescriptionRepositoryFactory->createWordDescriptionRepository());
}

std::shared_ptr<WordDescriptionGenerator> createWordDescriptionGenerator(
    const std::shared_ptr<WordDescriptionRetrieverService>& wordDescriptionRetrieverService)
{
    return std::make_shared<WordDescriptionConcurrentGenerator>(wordDescriptionRetrieverService);
}
}
}