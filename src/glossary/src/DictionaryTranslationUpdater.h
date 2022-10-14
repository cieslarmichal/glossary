#pragma once

#include "dictionaryService/Dictionary.h"

namespace glossary
{
class DictionaryTranslationUpdater
{
public:
    virtual ~DictionaryTranslationUpdater() = default;

    virtual void updateDictionaryWordTranslation(const dictionary::std::string&,
                                                 const std::string& updatedTranslation,
                                                 const dictionary::std::string&) = 0;
    virtual void updateDictionaryWordTranslation(const dictionary::std::string&,
                                                 const dictionary::std::string&) = 0;
    virtual void updateDictionaryTranslations(const dictionary::std::string&) = 0;
};
}