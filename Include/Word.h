#pragma once

#include "EnglishWord.h"
#include "PolishWord.h"
#include "WordDescription.h"

struct Word
{
    Word(EnglishWord e, PolishWord p , WordDescription wd): englishWord{e}, polishWord{p}, wordDescription{wd} {}

    EnglishWord englishWord;
    PolishWord polishWord;
    WordDescription wordDescription;
};


