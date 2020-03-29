#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "boost/optional.hpp"

namespace dictionaryRepository
{
struct DictionaryWord
{
    std::string englishWord;
    boost::optional<std::string> translation;
};

using DictionaryWords = std::vector<DictionaryWord>;

inline bool operator==(const DictionaryWord& lhs, const DictionaryWord& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.translation == rhs.translation);
}

inline std::ostream& operator<<(std::ostream& os, const DictionaryWord& dictionaryWord)
{
    os << "{englishWord: " << dictionaryWord.englishWord
       << ", translation: " << ((dictionaryWord.translation) ? "-" : *dictionaryWord.translation) << "}";
    return os;
}
}