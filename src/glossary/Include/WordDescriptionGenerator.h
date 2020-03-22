#pragma once

#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

class WordDescriptionGenerator
{
public:
    virtual ~WordDescriptionGenerator() = default;

    virtual wordDescriptionRepository::WordsDescriptions
    generateWordsDescriptions(const wordDescriptionRepository::EnglishWords&) = 0;
    virtual wordDescriptionRepository::WordDescription
    generateWordDescription(const wordDescriptionRepository::EnglishWord&) = 0;
};