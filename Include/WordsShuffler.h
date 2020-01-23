#pragma once

#include "wordsDb/descriptionsDb/WordsDescriptions.h"

using namespace wordsDb::descriptionsDb;

class WordsShuffler
{
public:
    virtual ~WordsShuffler() = default;

    virtual WordsDescriptions shuffle(const WordsDescriptions&) const = 0;
};
