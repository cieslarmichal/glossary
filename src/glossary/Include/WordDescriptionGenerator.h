#pragma once

#include "wordsDescriptionsDb/EnglishWord.h"
#include "wordsDescriptionsDb/WordDescription.h"

class WordDescriptionGenerator
{
public:
    virtual ~WordDescriptionGenerator() = default;

    virtual wordsDescriptionsDb::WordsDescriptions
    generateWordsDescriptions(const wordsDescriptionsDb::EnglishWords&) = 0;
    virtual wordsDescriptionsDb::WordDescription
    generateWordDescription(const wordsDescriptionsDb::EnglishWord&) = 0;
};