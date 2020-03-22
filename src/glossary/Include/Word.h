#pragma once

#include <ostream>
#include <memory>

#include "boost/optional.hpp"
#include "boost/optional/optional_io.hpp"

#include "PolishWord.h"
#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

struct Word
{
    Word(const PolishWord& polishWordInit, const wordDescriptionRepository::EnglishWord& englishWordInit,
         const boost::optional<wordDescriptionRepository::WordDescription>& wordDescriptionInit)
        : polishWord{polishWordInit}, englishWord{englishWordInit}, wordDescription{wordDescriptionInit}
    {
    }

    PolishWord polishWord;
    wordDescriptionRepository::EnglishWord englishWord;
    boost::optional<wordDescriptionRepository::WordDescription> wordDescription;
};

using UniqueWord = std::unique_ptr<Word>;

inline bool operator==(const Word& lhs, const Word& rhs)
{
    return (lhs.polishWord == rhs.polishWord && lhs.englishWord == rhs.englishWord &&
            lhs.wordDescription == rhs.wordDescription);
}

inline bool operator==(const Word& lhs, const UniqueWord& rhs)
{
    return (lhs == *rhs);
}

inline bool operator==(const UniqueWord& lhs, const Word& rhs)
{
    return (*lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Word& word)
{
    os << "{polishWord: " << word.polishWord << ", englishWord: " << word.englishWord
       << ", wordDescription: " << word.wordDescription << "}";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const UniqueWord& uniqueWord)
{
    os << *uniqueWord;
    return os;
}