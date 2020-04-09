#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "Application.h"
#include "ConnectionChecker.h"
#include "DictionarySynchronizer.h"
#include "DictionaryTranslationUpdater.h"
#include "UserPrompt.h"
#include "WordViewFormatter.h"
#include "dictionaryService/DictionaryService.h"
#include "statisticsRepository/StatisticsRepository.h"
#include "translationService/TranslationRetrieverService.h"
#include "wordDescriptionService/WordDescriptionRetrieverService.h"

namespace glossary
{
class GlossaryApplication : public Application
{
public:
    GlossaryApplication(std::shared_ptr<dictionaryService::DictionaryService>,
                        std::shared_ptr<translationService::TranslationRetrieverService>,
                        std::shared_ptr<statisticsRepository::StatisticsRepository>,
                        std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>,
                        std::shared_ptr<DictionarySynchronizer>,
                        std::shared_ptr<DictionaryTranslationUpdater>, std::unique_ptr<ConnectionChecker>,
                        std::unique_ptr<AnswerValidator>, std::unique_ptr<UserPrompt>);

    void run() override;

private:
    bool connectionIsAvailable() const;
    void initialize();
    void loop();
    void showMenu() const;
    void translate() const;
    void listDictionariesByNames();
    void listDictionaryWordsFromDictionary();
    void addDictionary() const;
    void addEnglishWordToDictionary() const;
    void removeDictionary() const;
    void removeEnglishWordFromDictionary() const;
    void addDictionaryFromFile() const;
    void updateDictionaryWordTranslationManually() const;
    void updateDictionaryWordTranslationAutomatically() const;
    void updateDictionaryTranslationsAutomatically() const;
    void guessWord() const;
    void getEnglishWordDescription() const;
    void showStatistics() const;
    void resetStatistics() const;

    std::shared_ptr<dictionaryService::DictionaryService> dictionaryService;
    std::shared_ptr<translationService::TranslationRetrieverService> translationRetrieverService;
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService> wordDescriptionRetrieverService;
    std::shared_ptr<DictionarySynchronizer> dictionarySynchronizer;
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdater;

    std::unique_ptr<ConnectionChecker> connectionChecker;
    std::unique_ptr<AnswerValidator> answerValidator;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewFormatter> wordViewFormatter;

    wordDescriptionRepository::EnglishWords englishWords;
};
}