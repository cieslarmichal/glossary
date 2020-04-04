#pragma once

#include "dictionaryRepository/DictionaryWord.h"

namespace glossary
{
class DictionaryWordRandomizer
{
public:
    virtual ~DictionaryWordRandomizer() = default;

    virtual dictionaryRepository::DictionaryWord
    randomize(const dictionaryRepository::DictionaryWords&) const = 0;
};
}