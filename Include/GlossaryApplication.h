#pragma once

#include <memory>

#include "AnswerChecker.h"
#include "AnswersCounter.h"
#include "Application.h"
#include "UserPrompt.h"
#include "WordRandomizer.h"
#include "WordViewer.h"
#include "WordsGeneratorService.h"

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
    std::unique_ptr<WordsGeneratorService> wordsGenerator;
    std::unique_ptr<AnswersCounter> answersCounter;
    std::unique_ptr<AnswerChecker> answerChecker;
    std::unique_ptr<UserPrompt> userPrompt;
    std::unique_ptr<WordViewer> viewer;
    std::unique_ptr<WordRandomizer> wordsRandomizer;
    Words glossaryWords;
};
