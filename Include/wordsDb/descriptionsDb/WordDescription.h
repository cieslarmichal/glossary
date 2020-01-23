#pragma once

#include "Description.h"
#include "EnglishWord.h"
#include "PolishWord.h"

namespace wordsDb::descriptionsDb
{
struct WordDescription
{
    // TODO: change to WordWithDescription and remove polishWord
    WordDescription() = default;

    WordDescription(EnglishWord e, PolishWord p, Description wd)
        : englishWord{e}, polishWord{p}, wordDescription{wd}
    {
    }

    std::string toString() const
    {
        return "WordDescription{" + englishWord + " " + polishWord + "\n" +
               wordDescription.toString();
    }

    EnglishWord englishWord;
    PolishWord polishWord;
    Description wordDescription;
};

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.polishWord == rhs.polishWord &&
            lhs.wordDescription == rhs.wordDescription);
}

inline std::ostream& operator<<(std::ostream& os, const WordDescription& word)
{
    os << "\n"
       << "englishWord: " << word.englishWord << "\n"
       << "polishWord: " << word.polishWord << "\n"
       << "wordDescription:" << word.wordDescription << "\n";
    return os;
}
}