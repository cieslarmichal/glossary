#pragma once

#include "Dictionary.h"
#include "boost/optional.hpp"

namespace glossary::dictionaryService
{
class RandomDictionaryWordRetriever
{
public:
    virtual ~RandomDictionaryWordRetriever() = default;

    virtual boost::optional<DictionaryWord> getRandomDictionaryWord() const = 0;
    virtual boost::optional<DictionaryWord> getRandomDictionaryWord(const DictionaryName&) const = 0;
};
}