#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "ConnectionChecker.h"
#include "DictionaryTranslationUpdater.h"
#include "Glossary.h"
#include "UserPrompt.h"
#include "WordViewFormatter.h"
#include "dictionaryService/DictionaryService.h"
#include "statisticsRepository/StatisticsRepository.h"
#include "translationService/TranslationRetrieverService.h"
#include "wordDescriptionService/WordDescriptionRetrieverService.h"

namespace glossary
{
class DefaultGlossary : public Glossary
{
public:
    DefaultGlossary(std::shared_ptr<dictionaryService::DictionaryService>,
                    std::shared_ptr<translationService::TranslationRetrieverService>,
                    std::shared_ptr<statisticsRepository::StatisticsRepository>,
                    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService>,
                    std::shared_ptr<DictionaryTranslationUpdater>,
                    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>>,
                    std::unique_ptr<ConnectionChecker>, std::unique_ptr<AnswerValidator>,
                    std::unique_ptr<UserPrompt>);

    void run() override;
    boost::optional<std::string> translate() const override;
    std::vector<std::string> listDictionariesByNames() override;
    std::vector<std::string> listDictionaryWordsFromDictionary() override;
    void addDictionary() const override;
    void addEnglishWordToDictionary() const override;
    void removeDictionary() const override;
    void removeEnglishWordFromDictionary() const override;
    void addDictionaryFromFile() const override;
    void updateDictionaryWordTranslationManually() const override;
    void updateDictionaryWordTranslationAutomatically() const override;
    void updateDictionaryTranslationsAutomatically() const override;
    void guessWord() const override;
    std::string getEnglishWordDescription() const override;
    std::vector<std::string> showStatistics() const override;
    void resetStatistics() const override;

private:
    bool connectionIsAvailable() const;
    void initialize();
    void loop();
    void showMenu() const;

    std::shared_ptr<dictionaryService::DictionaryService> dictionaryService;
    std::shared_ptr<translationService::TranslationRetrieverService> translationRetrieverService;
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService> wordDescriptionRetrieverService;
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdater;
    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>> dictionaryObservers;

    std::unique_ptr<ConnectionChecker> connectionChecker;
    std::unique_ptr<AnswerValidator> answerValidator;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewFormatter> wordViewFormatter;

    wordDescriptionRepository::EnglishWords englishWords;
};
}