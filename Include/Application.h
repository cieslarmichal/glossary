#pragma once

#include "WordsGeneratorService.h"
#include "AnswersCounter.h"
#include "WordViewer.h"

class Application
{
public:
    void run();

private:
    std::unique_ptr<WordsGeneratorService> wordsGenerator;
    std::unique_ptr<AnswersCounter> answersCounter;
    std::unique_ptr<WordViewer> viewer;
    //prompt
};