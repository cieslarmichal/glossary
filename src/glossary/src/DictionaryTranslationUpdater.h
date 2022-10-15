#pragma once

#include "dictionaryService/Dictionary.h"

namespace glossary
{
class DictionaryTranslationUpdater
{
public:
    virtual ~DictionaryTranslationUpdater() = default;

    virtual void updateDictionaryWordTranslation(const std::string&,
                                                 const std::string& updatedTranslation,
                                                 const std::string&) = 0;
    virtual void updateDictionaryWordTranslation(const std::string&,
                                                 const std::string&) = 0;
    virtual void updateDictionaryTranslations(const std::string&) = 0;
};
}