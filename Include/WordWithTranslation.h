#pragma once

#include <string>

struct WordWithTranslation
{
    bool operator==(const WordWithTranslation& rhs)
    {
        return (englishWord == rhs.englishWord && polishTranslation == rhs.polishTranslation);
    }

    std::string englishWord;
    std::string polishTranslation;
};

