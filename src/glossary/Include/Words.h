#pragma once

#include "Word.h"
#include <vector>
#include <memory>

using UniqueWords = std::vector<UniqueWord>;
using Words = std::vector<Word>;

inline bool operator==(const Words& words, const UniqueWords& uniqueWords)
{
    for(const auto& uniqueWord : uniqueWords)
    {
        const auto found = std::find(words.begin(), words.end(), *uniqueWord);
        if(found == words.end())
        {
            return false;
        }
    }
    return true;
}

inline bool operator==(const UniqueWords& uniqueWords, const Words& words)
{
    return words == uniqueWords;
}

