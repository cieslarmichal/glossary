#pragma once

#include "wordsDescriptionsDb/WordsDescriptions.h"

using namespace wordsDescriptionsDb;

class WordRandomizer
{
public:
    virtual ~WordRandomizer() = default;

    virtual WordDescription randomizeWord(const WordsDescriptions&) const = 0;
};