#pragma once

#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace glossary::dictionary
{
struct DictionaryWord
{
    std::string englishWord;
    std::optional<std::string> translation;
};

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