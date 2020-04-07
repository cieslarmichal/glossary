#pragma once

#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

namespace glossary
{
class WordDescriptionLoader
{
public:
    virtual ~WordDescriptionLoader() = default;

    virtual void loadWordsDescriptions(const wordDescriptionRepository::EnglishWords&) = 0;
};
}