#pragma once

#include <memory>

#include "TranslationLoader.h"
#include "translationRepository/TranslationRepository.h"
#include "translator/Translator.h"
#include "utils/SupportedThreadsCalculator.h"
#include "utils/ThreadSafeQueue.h"

namespace glossary
{
class TranslationConcurrentLoader : public TranslationLoader
{
public:
    TranslationConcurrentLoader(std::shared_ptr<translator::Translator>,
                                std::shared_ptr<translationRepository::TranslationRepository>);

    void loadMissingTranslations(const wordDescriptionRepository::EnglishWords&) override;

private:
    unsigned getAmountOfThreads() const;
    wordDescriptionRepository::EnglishWords
    getEnglishWordsWithoutTranslation(const wordDescriptionRepository::EnglishWords&) const;
    void loadingTranslationsWorker(utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>&,
                                   utils::ThreadSafeQueue<translationRepository::Translation>&);
    boost::optional<translationRepository::Translation>
    getTranslationFromTranslator(const wordDescriptionRepository::EnglishWord&);
    void loadTranslationsIntoRepository(const translationRepository::Translations&);

    std::shared_ptr<translator::Translator> translator;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
    utils::SupportedThreadsCalculator supportedThreadsCalculator;
};
}