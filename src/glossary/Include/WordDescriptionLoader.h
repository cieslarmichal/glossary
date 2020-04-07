#pragma once

#include "wordDescriptionRepository/EnglishWord.h"

namespace glossary
{
class WordDescriptionLoader
{
public:
    virtual ~WordDescriptionLoader() = default;

    virtual void loadMissingWordsDescriptions(const wordDescriptionRepository::EnglishWords&) = 0;
};
}