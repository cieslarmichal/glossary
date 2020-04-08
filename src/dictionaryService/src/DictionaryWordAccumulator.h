#pragma once

#include "boost/optional.hpp"

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class DictionaryWordAccumulator
{
public:
    DictionaryWords accumulateDictionaryWords(const Dictionary&) const;
    DictionaryWords accumulateDictionaryWords(const Dictionaries&) const;
    EnglishWords accumulateEnglishWords(const Dictionary&) const;
    EnglishWords accumulateEnglishWords(const Dictionaries&) const;
};
}