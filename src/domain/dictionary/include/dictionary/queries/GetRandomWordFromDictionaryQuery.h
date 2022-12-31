#pragma once

#include <string>

#include "../Dictionary.h"
#include "../DictionaryWord.h"

namespace glossary::dictionary
{
class GetRandomWordFromDictionaryQuery
{
public:
    virtual ~GetRandomWordFromDictionaryQuery() = default;

    virtual DictionaryWord getRandomWord(const std::string& dictionaryName) const = 0;
};
}
