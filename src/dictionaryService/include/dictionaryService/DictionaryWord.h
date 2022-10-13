#pragma once

#include <boost/optional.hpp>
#include <ostream>
#include <string>
#include <vector>



namespace glossary::dictionaryService
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

inline std::string toString(const DictionaryWord& dictionaryWord)
{
    std::string translationAsString = (dictionaryWord.translation) ? *dictionaryWord.translation : "-";
    return "{englishWord:" + dictionaryWord.englishWord + ",translation:" + translationAsString + "}";
}

inline std::ostream& operator<<(std::ostream& os, const DictionaryWord& dictionaryWord)
{
    return os << toString(dictionaryWord);
}
}