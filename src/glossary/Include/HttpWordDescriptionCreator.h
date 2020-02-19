#pragma once

#include "wordsDescriptionsDb/WordDescription.h"

class HttpWordDescriptionCreator
{
public:
    virtual ~HttpWordDescriptionCreator() = default;

    virtual boost::optional<wordsDescriptionsDb::WordDescription>
    createWordDescription(const wordsDescriptionsDb::EnglishWord&) const = 0;
    virtual wordsDescriptionsDb::WordsDescriptions
    createWordsDescriptions(const wordsDescriptionsDb::EnglishWords&) const = 0;
};