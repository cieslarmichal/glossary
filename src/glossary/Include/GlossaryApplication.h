#pragma once

#include <memory>

#include "AnswerChecker.h"
#include "Application.h"
#include "DictionaryReader.h"
#include "UserPrompt.h"
#include "WordDescriptionGenerator.h"
#include "WordRandomizer.h"
#include "WordViewer.h"
#include "statisticsDb/StatisticsDb.h"
#include "wordsDescriptionsDb/WordsDescriptionsDb.h"

// TODO: move std::cin from UserPrompt to application

class GlossaryApplication : public Application
{
public:
    GlossaryApplication();

    void run() override;

private:
    void initialize();
    void loop();

    // TODO: add const into unique_ptr if possible
    std::unique_ptr<WordDescriptionGenerator> wordDescriptionGenerator;
    std::unique_ptr<statisticsDb::StatisticsDb> statisticsDb;
    std::unique_ptr<AnswerChecker> answerChecker;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewer> viewer;
    std::unique_ptr<WordRandomizer> wordsRandomizer;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::shared_ptr<wordsDescriptionsDb::WordsDescriptionsDb>
        wordsDescriptionsDb;
    Dictionary dictionary;
    EnglishWords englishWords;
    Words glossaryWords;
};
