#pragma once

#include <memory>

#include "dictionaryService/DictionaryObserver.h"
#include "translationRepository/TranslationRepository.h"
#include "translationService/TranslationService.h"
#include "utils/SupportedThreadsCalculator.h"
#include "utils/ThreadSafeQueue.h"

namespace glossary
{
class TranslationConcurrentUpdater : public dictionaryService::DictionaryObserver
{
public:
    TranslationConcurrentUpdater(std::shared_ptr<translationService::TranslationService>,
                                 std::shared_ptr<translationRepository::TranslationRepository>);

    void update(const dictionaryService::EnglishWords&) override;

private:
    unsigned getAmountOfThreads() const;
    dictionaryService::EnglishWords
    getEnglishWordsWithoutTranslation(const dictionaryService::EnglishWords&) const;
    void loadingTranslationsWorker(utils::ThreadSafeQueue<dictionaryService::EnglishWord>&);
    void loadTranslationFromTranslationService(const dictionaryService::EnglishWord&);

    std::shared_ptr<translationService::TranslationService> translationService;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
    utils::SupportedThreadsCalculator supportedThreadsCalculator;
};
}