#pragma once

#include <memory>
#include <ostream>
#include <utility>

#include "boost/optional.hpp"
#include "boost/optional/optional_io.hpp"

#include "PolishWord.h"
#include "wordDescriptionRepository/EnglishWord.h"
#include "wordDescriptionRepository/WordDescription.h"

struct Word
{
    Word(wordDescriptionRepository::EnglishWord englishWordInit, boost::optional<PolishWord> polishWordInit,
         boost::optional<wordDescriptionRepository::WordDescription> wordDescriptionInit)
        : englishWord{std::move(englishWordInit)},
          polishTranslation{std::move(polishWordInit)},
          wordDescription{std::move(wordDescriptionInit)}
    {
    }

    wordDescriptionRepository::EnglishWord englishWord;
    boost::optional<PolishWord> polishTranslation;
    boost::optional<wordDescriptionRepository::WordDescription> wordDescription;
};

using UniqueWord = std::unique_ptr<Word>;

inline bool operator==(const Word& lhs, const Word& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.polishTranslation == rhs.polishTranslation &&
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
    os << "{englishWord: " << word.englishWord << ", polishTranslation: " << word.polishTranslation
       << ", wordDescription: " << word.wordDescription << "}";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const UniqueWord& uniqueWord)
{
    return os << *uniqueWord;
}