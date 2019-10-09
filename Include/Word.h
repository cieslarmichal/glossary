#pragma once

#include "EnglishWord.h"
#include "PolishWord.h"
#include "WordDescription.h"

struct Word
{
    Word(EnglishWord e, PolishWord p, WordDescription wd) : englishWord{e}, polishWord{p}, wordDescription{wd}
    {}

    std::string toString() const
    {
        return englishWord + " " + polishWord + "\n" + wordDescription.toString();
    }

    EnglishWord englishWord;
    PolishWord polishWord;
    WordDescription wordDescription;
};

inline bool operator==(const Word& lhs, const Word& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.polishWord == rhs.polishWord &&
            lhs.wordDescription == rhs.wordDescription);
}

inline std::ostream& operator<<(std::ostream& os, const Word& word)
{
    os << word.toString();
    return os;
}

