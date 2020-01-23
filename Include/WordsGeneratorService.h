#pragma once

#include "wordsDb/descriptionsDb/WordsDescriptions.h"
#include "wordsDb/translationsDb/Translation.h"

class WordsGeneratorService
{
public:
    virtual ~WordsGeneratorService() = default;

    virtual wordsDb::descriptionsDb::WordDescription
    generateWord(const wordsDb::translationsDb::Translation&) const = 0;
    virtual wordsDb::descriptionsDb::WordsDescriptions
    generateWords() const = 0;
};