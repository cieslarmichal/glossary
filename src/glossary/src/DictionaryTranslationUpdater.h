#pragma once

#include "dictionaryService/Dictionary.h"

namespace glossary
{
class DictionaryTranslationUpdater
{
public:
    virtual ~DictionaryTranslationUpdater() = default;

    virtual void updateDictionaryWordTranslation(const dictionaryService::std::string&,
                                                 const std::string& updatedTranslation,
                                                 const dictionaryService::DictionaryName&) = 0;
    virtual void updateDictionaryWordTranslation(const dictionaryService::std::string&,
                                                 const dictionaryService::DictionaryName&) = 0;
    virtual void updateDictionaryTranslations(const dictionaryService::DictionaryName&) = 0;
};
}