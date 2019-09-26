#pragma once

#include "EnglishWord.h"
#include "PolishWord.h"

struct WordWithTranslation
{
    bool operator==(const WordWithTranslation& rhs)
    {
        return (englishWord == rhs.englishWord && polishTranslation == rhs.polishTranslation);
    }

    EnglishWord englishWord;
    PolishWord polishTranslation;
};

