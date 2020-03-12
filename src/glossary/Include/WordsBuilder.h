#pragma once

#include "Word.h"
#include "translationsDb/Translation.h"
#include "wordsDescriptionsDb/WordDescription.h"

class WordsBuilder
{
public:
    virtual ~WordsBuilder() = default;

    virtual Words buildWords(const translationsDb::Translations&,
                             const wordsDescriptionsDb::WordsDescriptions&) const = 0;
};