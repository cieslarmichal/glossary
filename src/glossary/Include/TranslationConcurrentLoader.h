#pragma once

#include <memory>

#include "TranslationLoader.h"
#include "translationRepository/TranslationRepository.h"
#include "translationService/TranslationRetrieverService.h"
#include "utils/SupportedThreadsCalculator.h"
#include "utils/ThreadSafeQueue.h"

namespace glossary
{
class TranslationConcurrentLoader : public TranslationLoader
{
public:
    TranslationConcurrentLoader(std::shared_ptr<translationService::TranslationRetrieverService>,
                                std::shared_ptr<translationRepository::TranslationRepository>);

    void loadMissingTranslations(const wordDescriptionRepository::EnglishWords&) override;

private:
    unsigned getAmountOfThreads() const;
    wordDescriptionRepository::EnglishWords
    getEnglishWordsWithoutTranslation(const wordDescriptionRepository::EnglishWords&) const;
    void loadingTranslationsWorker(utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>&);
    void loadTranslationFromTranslationService(const wordDescriptionRepository::EnglishWord&);

    std::shared_ptr<translationService::TranslationRetrieverService> translationService;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
    utils::SupportedThreadsCalculator supportedThreadsCalculator;
};
}