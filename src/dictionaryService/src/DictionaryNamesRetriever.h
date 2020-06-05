#pragma once

#include "DictionaryName.h"

namespace glossary::dictionaryService
{
class DictionaryNamesRetriever
{
public:
    virtual ~DictionaryNamesRetriever() = default;

    virtual DictionaryNames retrieveDictionaryNames() const = 0;
    virtual DictionaryNames
    retrieveDictionaryNamesContainingEnglishWord(const std::string& englishWord) const = 0;
    virtual DictionaryNames retrieveDictionaryNamesContainingEnglishWordTranslation(
        const std::string& englishWordTranslation) const = 0;
};
}