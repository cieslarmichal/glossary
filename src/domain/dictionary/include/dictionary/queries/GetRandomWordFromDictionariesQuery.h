#pragma once

#include <string>

#include "../Dictionary.h"

namespace glossary::dictionary
{
class GetRandomWordFromDictionariesQuery
{
public:
    virtual ~GetRandomWordFromDictionariesQuery() = default;

    virtual DictionaryWord getRandomWord() const = 0;
};
}
