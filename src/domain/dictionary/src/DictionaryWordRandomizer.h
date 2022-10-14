#pragma once

#include "DictionaryWord.h"

namespace glossary::dictionary
{
class DictionaryWordRandomizer
{
public:
    virtual ~DictionaryWordRandomizer() = default;

    virtual DictionaryWord randomize(const std::vector<DictionaryWord>&) const = 0;
};
}