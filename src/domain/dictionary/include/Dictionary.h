#pragma once

#include <ostream>
#include <vector>

#include "DictionaryWord.h"
#include "StlOperators.h"

namespace glossary::dictionary
{
struct Dictionary
{
    std::string name;
    std::vector<DictionaryWord> words;
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