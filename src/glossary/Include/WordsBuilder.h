#pragma once

#include "Word.h"
#include "translationsDb/Translation.h"
#include "wordDescriptionRepository/WordDescription.h"

class WordsBuilder
{
public:
    virtual ~WordsBuilder() = default;

    virtual Words buildWords(const translationsDb::Translations&,
                             const wordDescriptionRepository::WordsDescriptions&) const = 0;
};