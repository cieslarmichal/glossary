#pragma once

#include "Words.h"
#include "WordWithTranslation.h"

class WordsGeneratorService
{
public:
    virtual ~WordsGeneratorService() = default;

    virtual Word generateWord(const WordWithTranslation&) const = 0;
    virtual Words generateWords() const = 0;
};