#pragma once

#include "wordsDb/translationsDb/Translation.h"
#include "wordsDb/wordsDescriptionsDb/WordsDescriptions.h"

class WordsGeneratorService
{
public:
    virtual ~WordsGeneratorService() = default;

    virtual wordsDb::wordsDescriptionsDb::WordDescription
    generateWord(const wordsDb::translationsDb::Translation&) const = 0;
    virtual wordsDb::wordsDescriptionsDb::WordsDescriptions
    generateWords() const = 0;
};