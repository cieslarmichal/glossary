#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "Application.h"
#include "TranslationRetrieverService.h"
#include "UserPrompt.h"
#include "WordDescriptionGenerator.h"
#include "WordDescriptionRetrieverService.h"
#include "WordViewFormatter.h"
#include "dictionaryService/DictionaryService.h"
#include "statisticsRepository/StatisticsRepository.h"
#include "utils/FileAccess.h"

namespace glossary
{
class GlossaryApplication : public Application
{
public:
    // TODO: add check connection with merriam webster with start application
    // TODO: services in separate libs
    GlossaryApplication(std::shared_ptr<dictionaryService::DictionaryService>,
                        std::shared_ptr<TranslationRetrieverService>,
                        std::shared_ptr<statisticsRepository::StatisticsRepository>,
                        std::shared_ptr<WordDescriptionRetrieverService>,
                        std::shared_ptr<WordDescriptionGenerator>, std::unique_ptr<AnswerValidator>,
                        std::unique_ptr<UserPrompt>);

    void run() override;

private:
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
    void guessWord() const;
    void getEnglishWordDescription() const;
    void showStatistics() const;
    void resetStatistics() const;

    std::shared_ptr<utils::FileAccess> fileAccess;
    std::shared_ptr<dictionaryService::DictionaryService> dictionaryService;
    std::shared_ptr<TranslationRetrieverService> translationRetrieverService;
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::shared_ptr<WordDescriptionRetrieverService> wordDescriptionRetrieverService;
    std::shared_ptr<WordDescriptionGenerator> wordDescriptionGenerator;

    std::unique_ptr<AnswerValidator> answerValidator;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewFormatter> wordViewFormatter;

    wordDescriptionRepository::EnglishWords englishWords;
};
}