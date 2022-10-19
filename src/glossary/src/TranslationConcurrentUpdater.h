#pragma once

#include <memory>

#include "DictionaryObserver.h"
#include "SupportedThreadsCalculator.h"
#include "TranslationRepository.h"
#include "TranslationService.h"
#include "collection/ThreadSafeQueue.h"

namespace glossary
{
class TranslationConcurrentUpdater : public dictionary::DictionaryObserver
{
public:
    TranslationConcurrentUpdater(std::shared_ptr<translationService::TranslationService>,
                                 std::shared_ptr<translation::TranslationRepository>);

    void update(const dictionary::std::vector<std::string>&) override;

private:
    unsigned getAmountOfThreads() const;
    dictionary::std::vector<std::string>
    getEnglishWordsWithoutTranslation(const dictionary::std::vector<std::string>&) const;
    void loadingTranslationsWorker(common::ThreadSafeQueue<std::string>&);
    void loadTranslationFromTranslationService(const std::string&);

    std::shared_ptr<translationService::TranslationService> translationService;
    std::shared_ptr<translation::TranslationRepository> translationRepository;
    common::SupportedThreadsCalculator supportedThreadsCalculator;
};
}