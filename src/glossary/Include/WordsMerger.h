#pragma once

#include "Words.h"
#include "dictionaryRepository/Dictionary.h"
#include "wordDescriptionRepository/WordDescription.h"

namespace glossary
{
class WordsMerger
{
public:
    virtual ~WordsMerger() = default;

    virtual UniqueWords mergeWords(const dictionaryRepository::DictionaryWords&,
                                   const wordDescriptionRepository::WordsDescriptions&) const = 0;
};
}