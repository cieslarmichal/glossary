#pragma once

#include "Words.h"

class WordsGeneratorService
{
public:
    virtual ~WordsGeneratorService() = default;

    virtual Words generateWords() const = 0;
};