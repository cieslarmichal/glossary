#pragma once

#include "boost/optional.hpp"

#include "Dictionary.h"

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