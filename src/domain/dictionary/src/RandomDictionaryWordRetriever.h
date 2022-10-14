#pragma once

#include <optional>

#include "Dictionary.h"

namespace glossary::dictionary
{
class RandomDictionaryWordRetriever
{
public:
    virtual ~RandomDictionaryWordRetriever() = default;

    virtual std::optional<DictionaryWord> getRandomDictionaryWord() const = 0;
    virtual std::optional<DictionaryWord> getRandomDictionaryWord(const std::string&) const = 0;
};
}