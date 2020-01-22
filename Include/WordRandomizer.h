#pragma once

#include "wordsDb/descriptionsDb/WordsDescriptions.h"

class WordRandomizer
{
public:
    virtual ~WordRandomizer() = default;

    virtual WordDescription randomizeWord(const Words&) const = 0;
};