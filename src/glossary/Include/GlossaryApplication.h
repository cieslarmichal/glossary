#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "Application.h"
#include "StatisticsModifierService.h"
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
    void guessWord() const;
    void translate() const;
    void listDictionaries() const;

    std::shared_ptr<utils::FileAccess> fileAccess;
    std::unique_ptr<WordDescriptionGenerator> wordDescriptionGenerator;
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::shared_ptr<StatisticsModifierService> statisticsModifierService;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    std::shared_ptr<translationRepository::TranslationRepository> translationRepository;
    std::shared_ptr<dictionaryRepository::DictionaryRepository> dictionaryRepository;
    std::shared_ptr<TranslationRetrieverService> translationRetrieverService;
    std::unique_ptr<AnswerValidator> answerValidator;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewFormatter> wordViewFormatter;
    std::unique_ptr<WordRandomizer> wordsRandomizer;
    std::unique_ptr<WordsMerger> wordsMerger;
    dictionaryRepository::Dictionaries dictionaries;
    wordDescriptionRepository::EnglishWords englishWords;
    UniqueWords glossaryWords;
    Words wordsWithTranslation;
};
