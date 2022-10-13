#pragma once

#include <memory>

#include "../../domain/translation/include/TranslationRepository.h"
#include "dictionaryService/DictionaryObserver.h"
#include "translationService/TranslationService.h"
#include "utils/SupportedThreadsCalculator.h"
#include "utils/ThreadSafeQueue.h"

namespace glossary
{
class TranslationConcurrentUpdater : public dictionaryService::DictionaryObserver
{
public:
    TranslationConcurrentUpdater(std::shared_ptr<translationService::TranslationService>,
                                 std::shared_ptr<translation::TranslationRepository>);

    void update(const dictionaryService::EnglishWords&) override;

private:
    unsigned getAmountOfThreads() const;
    dictionaryService::EnglishWords
    getEnglishWordsWithoutTranslation(const dictionaryService::EnglishWords&) const;
    void loadingTranslationsWorker(utils::ThreadSafeQueue<dictionaryService::EnglishWord>&);
    void loadTranslationFromTranslationService(const dictionaryService::EnglishWord&);

    std::shared_ptr<translationService::TranslationService> translationService;
    std::shared_ptr<translation::TranslationRepository> translationRepository;
    utils::SupportedThreadsCalculator supportedThreadsCalculator;
};
}