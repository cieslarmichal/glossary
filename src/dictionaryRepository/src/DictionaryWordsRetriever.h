#pragma once

#include "DictionaryWord.h"

namespace glossary::dictionaryService
{
class DictionaryWordsRetriever
{
public:
    virtual ~DictionaryWordsRetriever() = default;

    virtual DictionaryWords retrieveDictionaryWords(const DictionaryName&) const = 0;
};
}