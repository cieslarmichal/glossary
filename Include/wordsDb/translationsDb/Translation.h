#pragma once

#include <ostream>

#include "EnglishWord.h"
#include "PolishWord.h"

namespace wordsDb::translationsDb
{

struct Translation
{
    EnglishWord englishWord;
    PolishWord polishTranslation;
};

inline bool operator==(const Translation& lhs, const Translation& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.polishTranslation == rhs.polishTranslation);
}

inline std::ostream& operator<<(std::ostream& os,
                                const Translation& translation)
{
    os << translation.englishWord << " " << translation.polishTranslation;
    return os;
}
}
