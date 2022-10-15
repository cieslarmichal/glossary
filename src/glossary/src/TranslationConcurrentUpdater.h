#pragma once

#include <memory>

#include "../../common/collection/include/ThreadSafeQueue.h"
#include "../../common/concurrency/include/SupportedThreadsCalculator.h"
#include "../../domain/translation/include/TranslationRepository.h"
#include "dictionaryService/DictionaryObserver.h"
#include "translationService/TranslationService.h"

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