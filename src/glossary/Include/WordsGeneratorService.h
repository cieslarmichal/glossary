#pragma once

#include <vector>

#include "Word.h"
#include "translationsDb/Translation.h"

class WordsGeneratorService
{
public:
    virtual ~WordsGeneratorService() = default;

    virtual Word generateWord(const translationsDb::Translation&) const = 0;
    virtual std::vector<Word> generateWords() const = 0;
};