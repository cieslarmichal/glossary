#pragma once

#include "wordDescriptionRepository/EnglishWord.h"

namespace glossary
{
class TranslationLoader
{
public:
    virtual ~TranslationLoader() = default;

    virtual void loadMissingTranslations(const wordDescriptionRepository::EnglishWords&) = 0;
};
}