#include "DefaultGlossaryFactory.h"

#include "DefaultDictionaryStatisticsCounter.h"
#include "DefaultGlossary.h"
#include "fileSystem/FileAccessFactory.h"
#include "httpClient/HttpClientFactory.h"
#include "TranslationConcurrentUpdater.h"
#include "WordDescriptionConcurrentUpdater.h"

namespace glossary
{

std::unique_ptr<Glossary> DefaultGlossaryFactory::createGlossary() const
{
    auto dictionaryStatisticsCounter = std::make_unique<DefaultDictionaryStatisticsCounter>();

    auto fileAccess = common::fileSystem::FileAccessFactory::createFileAccessFactory()->createDefaultFileAccess();
    auto httpClient = common::httpClient::HttpClientFactory::createHttpClientFactory()->createHttpClient();

    auto

//    auto dictionaryTranslationUpdater = createDictionaryTranslationUpdater(dictionaryService, translationService);
//
//    auto wordDescriptionUpdater = createWordDescriptionUpdater(wordDescriptionService, wordDescriptionRepository);
//    auto translationUpdater = createTranslationUpdater(translationService, translationRepository);
//    std::vector<std::shared_ptr<dictionary::DictionaryObserver>> observers{wordDescriptionUpdater, translationUpdater};


    return std::make_unique<DefaultGlossary>(dictionaryStatisticsCounter);
}
}
