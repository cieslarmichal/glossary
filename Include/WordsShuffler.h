#pragma once

#include "wordsDb/wordsDescriptionsDb/WordsDescriptions.h"

using namespace wordsDb::wordsDescriptionsDb;

class WordsShuffler
{
public:
    virtual ~WordsShuffler() = default;

    virtual WordsDescriptions shuffle(const WordsDescriptions&) const = 0;
};
