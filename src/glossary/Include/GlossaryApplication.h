#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "Application.h"
#include "TranslationRetrieverService.h"
#include "UserPrompt.h"
#include "WordDescriptionGenerator.h"
#include "WordRandomizer.h"
#include "WordViewFormatter.h"
#include "WordsMerger.h"
#include "dictionaryRepository/DictionaryRepository.h"
#include "statisticsRepository/StatisticsRepository.h"
#include "translationRepository/TranslationRepository.h"
#include "utils/FileAccess.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"

// TODO: move std::cin from UserPrompt to application

class GlossaryApplication : public Application
{
public:
    explicit GlossaryApplication(std::shared_ptr<utils::FileAccess>);

    void run() override;

private:
    void initialize();
    void loop();
    boost::optional<Word> randomizeWord(const Words&) const;
    boost::optional<Word> randomizeWordWithTranslation() const;
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

    std::shared_ptr<utils::FileAccess> fileAccess;
    std::shared_ptr<dictionaryRepository::DictionaryRepository> dictionaryRepository;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::unique_ptr<WordDescriptionGenerator> wordDescriptionGenerator;
    std::shared_ptr<TranslationRetrieverService> translationRetrieverService;
    std::unique_ptr<WordsMerger> wordsMerger;
    std::unique_ptr<WordRandomizer> wordsRandomizer;

    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<AnswerValidator> answerValidator;
    std::unique_ptr<WordViewFormatter> wordViewFormatter;

    dictionaryRepository::Dictionaries dictionaries;
    wordDescriptionRepository::EnglishWords englishWords;
    UniqueWords glossaryWords;
    Words wordsWithTranslation;
};
