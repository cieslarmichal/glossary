#pragma once

#include "translationsDb/Translation.h"
#include "wordsDescriptionsDb/WordsDescriptions.h"

class WordsGeneratorService
{
public:
    virtual ~WordsGeneratorService() = default;

    virtual wordsDescriptionsDb::WordDescription
    generateWord(const translationsDb::Translation&) const = 0;
    virtual wordsDescriptionsDb::WordsDescriptions
    generateWords() const = 0;
};