#pragma once

#include "DictionaryWord.h"

namespace glossary::dictionaryService
{
class DictionaryWordRandomizer
{
public:
    virtual ~DictionaryWordRandomizer() = default;

    virtual DictionaryWord
    randomize(const DictionaryWords&) const = 0;
};
}