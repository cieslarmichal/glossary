#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "Application.h"
#include "DictionaryReader.h"
#include "UserPrompt.h"
#include "WordDescriptionGenerator.h"
#include "WordRandomizer.h"
#include "WordViewFormatter.h"
#include "WordsMerger.h"
#include "statisticsRepository/StatisticsRepository.h"
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
    boost::optional<Word> randomizeWord() const;

    std::shared_ptr<utils::FileAccess> fileAccess;
    std::unique_ptr<WordDescriptionGenerator> wordDescriptionGenerator;
    std::unique_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
    std::unique_ptr<AnswerValidator> answerValidator;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewFormatter> wordViewFormatter;
    std::unique_ptr<WordRandomizer> wordsRandomizer;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    std::unique_ptr<WordsMerger> wordsMerger;
    Dictionaries dictionaries;
    Dictionary baseDictionary;
    wordDescriptionRepository::EnglishWords englishWords;
    UniqueWords glossaryWords;
};
