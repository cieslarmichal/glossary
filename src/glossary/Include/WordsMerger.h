#pragma once

#include "Words.h"
#include "translationRepository/Translation.h"
#include "wordDescriptionRepository/WordDescription.h"

class WordsMerger
{
public:
    virtual ~WordsMerger() = default;

    virtual UniqueWords mergeWords(const translationRepository::Translations&,
                             const wordDescriptionRepository::WordsDescriptions&) const = 0;
};