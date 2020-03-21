#pragma once

#include <memory>

#include "AnswerValidator.h"
#include "Application.h"
#include "DictionaryReader.h"
#include "UserPrompt.h"
#include "WordDescriptionGenerator.h"
#include "WordRandomizer.h"
#include "WordViewFormatter.h"
#include "WordsBuilder.h"
#include "statisticsDb/StatisticsDb.h"
#include "utils/FileAccess.h"
#include "wordsDescriptionsDb/WordsDescriptionsDb.h"

// TODO: move std::cin from UserPrompt to application

class GlossaryApplication : public Application
{
public:
    explicit GlossaryApplication(std::shared_ptr<utils::FileAccess>);

    void run() override;

private:
    void initialize();
    void loop();

    std::shared_ptr<utils::FileAccess> fileAccess;
    std::unique_ptr<WordDescriptionGenerator> wordDescriptionGenerator;
    std::unique_ptr<statisticsDb::StatisticsDb> statisticsDb;
    std::unique_ptr<AnswerValidator> answerValidator;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewFormatter> wordViewFormatter;
    std::unique_ptr<WordRandomizer> wordsRandomizer;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb> wordsDescriptionsDb;
    std::unique_ptr<WordsBuilder> wordsBuilder;
    Dictionaries dictionaries;
    Dictionary baseDictionary;
    wordsDescriptionsDb::EnglishWords englishWords;
    Words glossaryWords;
};
