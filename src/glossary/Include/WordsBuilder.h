#pragma once

#include "Word.h"
#include "translationRepository/Translation.h"
#include "wordDescriptionRepository/WordDescription.h"

class WordsBuilder
{
public:
    //TODO: change class name
    virtual ~WordsBuilder() = default;

    virtual Words buildWords(const translationRepository::Translations&,
                             const wordDescriptionRepository::WordsDescriptions&) const = 0;
};