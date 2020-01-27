#pragma once

#include "wordsDb/wordsDescriptionsDb/WordsDescriptions.h"

using namespace wordsDb::wordsDescriptionsDb;

class WordRandomizer
{
public:
    virtual ~WordRandomizer() = default;

    virtual WordDescription randomizeWord(const WordsDescriptions&) const = 0;
};