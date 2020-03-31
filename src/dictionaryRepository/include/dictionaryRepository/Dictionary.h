#pragma once

#include <ostream>
#include <vector>

#include "DictionaryName.h"
#include "DictionaryWord.h"
#include "utils/StlOperators.h"

namespace dictionaryRepository
{
struct Dictionary
{
    DictionaryName name;
    DictionaryWords words;
};

using Dictionaries = std::vector<Dictionary>;

inline bool operator==(const Dictionary& lhs, const Dictionary& rhs)
{
    return (lhs.name == rhs.name && lhs.words == rhs.words);
}

inline std::ostream& operator<<(std::ostream& os, const Dictionary& dictionary)
{
    os << "{name: " << dictionary.name << ", words: " << dictionary.words << "}";
    return os;
}
}