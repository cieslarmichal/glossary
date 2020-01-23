#pragma once

#include "wordsDb/descriptionsDb/WordsDescriptions.h"

using namespace wordsDb::descriptionsDb;

class WordRandomizer
{
public:
    virtual ~WordRandomizer() = default;

    virtual WordDescription randomizeWord(const WordsDescriptions&) const = 0;
};