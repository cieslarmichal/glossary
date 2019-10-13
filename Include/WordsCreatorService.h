#pragma once

#include "Words.h"

class WordsCreatorService
{
public:
    virtual ~WordsCreatorService() = default;

    virtual Words createWords() const = 0;
};