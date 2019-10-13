#pragma once

#include "WordsGeneratorService.h"
#include <memory>

class Application
{
public:
    void run();

private:
    std::unique_ptr<WordsGeneratorService> wordsGenerator;
    //words counter good answers
    //words randomizer
    //words displayer
};