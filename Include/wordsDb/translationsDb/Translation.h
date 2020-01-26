#pragma once

#include <ostream>

#include "EnglishWord.h"
#include "PolishWord.h"

namespace wordsDb::translationsDb
{

struct Translation
{
    PolishWord polishWord;
    EnglishWord englishWord;
};

inline bool operator==(const Translation& lhs, const Translation& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.polishWord == rhs.polishWord);
}

inline std::ostream& operator<<(std::ostream& os,
                                const Translation& translation)
{
    os << translation.englishWord << " " << translation.polishWord;
    return os;
}
}
