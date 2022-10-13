#pragma once

#include <memory>

#include "../../common/collection/include/ThreadSafeQueue.h"
#include "../../common/concurrency/include/SupportedThreadsCalculator.h"
#include "../../domain/translation/include/TranslationRepository.h"
#include "dictionaryService/DictionaryObserver.h"
#include "translationService/TranslationService.h"

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
    void loadingTranslationsWorker(common::ThreadSafeQueue<dictionaryService::std::string>&);
    void loadTranslationFromTranslationService(const dictionaryService::std::string&);

    std::shared_ptr<translationService::TranslationService> translationService;
    std::shared_ptr<translation::TranslationRepository> translationRepository;
    common::SupportedThreadsCalculator supportedThreadsCalculator;
};
}