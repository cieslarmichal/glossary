#pragma once

#include <ostream>
#include <vector>

#include "boost/optional.hpp"
#include "boost/optional/optional_io.hpp"

#include "EnglishWord.h"
#include "PolishWord.h"
#include "wordsDescriptionsDb/WordDescription.h"

struct Word
{
    PolishWord polishWord;
    EnglishWord englishWord;
    boost::optional<wordsDescriptionsDb::WordDescription> wordDescription;
};

using Words = std::vector<Word>;

inline bool operator==(const Word& lhs, const Word& rhs)
{
    return (lhs.polishWord == rhs.polishWord && lhs.englishWord == rhs.englishWord &&
            lhs.wordDescription == rhs.wordDescription);
}

inline std::ostream& operator<<(std::ostream& os, const Word& word)
{
    os << "{polishWord: " << word.polishWord << ", englishWord: " << word.englishWord
       << ", wordDescription: " << word.wordDescription << "}";
    return os;
}