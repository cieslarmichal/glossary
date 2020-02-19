#pragma once

#include "wordsDescriptionsDb/EnglishWord.h"
#include "wordsDescriptionsDb/WordDescription.h"

class WordDescriptionGenerator
{
public:
    virtual ~WordDescriptionGenerator() = default;

    virtual wordsDescriptionsDb::WordDescription
    generateWordDescription(const wordsDescriptionsDb::EnglishWord&) const = 0;
    // TODO: generateWords with multiple threads
    virtual wordsDescriptionsDb::WordsDescriptions generateWordsDescriptions(
        const wordsDescriptionsDb::EnglishWords&) const = 0;
};