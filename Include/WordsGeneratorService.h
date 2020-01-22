#pragma once

#include "wordsDb/descriptionsDb/WordsDescriptions.h"
#include "wordsDb/translationsDb/Translation.h"

class WordsGeneratorService
{
public:
    virtual ~WordsGeneratorService() = default;

    virtual WordDescription
    generateWord(const wordsDb::translationsDb::Translation&) const = 0;
    virtual Words generateWords() const = 0;
};