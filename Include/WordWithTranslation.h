#pragma once

#include <ostream>

#include "EnglishWord.h"
#include "PolishWord.h"

struct WordWithTranslation
{
    EnglishWord englishWord;
    PolishWord polishTranslation;
};

inline bool operator==(const WordWithTranslation& lhs,
                       const WordWithTranslation& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.polishTranslation == rhs.polishTranslation);
}

inline std::ostream& operator<<(std::ostream& os,
                                const WordWithTranslation& wordWithTranslation)
{
    os << wordWithTranslation.englishWord << " "
       << wordWithTranslation.polishTranslation;
    return os;
}
