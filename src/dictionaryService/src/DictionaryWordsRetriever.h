#pragma once

#include "DictionaryWord.h"

namespace glossary::dictionaryService
{
class DictionaryWordsRetriever
{
public:
    virtual ~DictionaryWordsRetriever() = default;

    virtual boost::optional<DictionaryWords> retrieveDictionaryWords(const DictionaryName&) const = 0;
    virtual boost::optional<EnglishWords> retrieveEnglishWords(const DictionaryName&) const = 0;
    virtual EnglishWords retrieveEnglishWords() const = 0;
};
}