#pragma once

#include "wordsDescriptionsDb/WordsDescriptions.h"

using namespace wordsDescriptionsDb;

class WordsShuffler
{
public:
    virtual ~WordsShuffler() = default;

    virtual WordsDescriptions shuffle(const WordsDescriptions&) const = 0;
};
