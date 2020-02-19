#pragma once

#include "Description.h"
#include "EnglishWord.h"

namespace wordsDescriptionsDb
{
struct WordDescription
{
    WordDescription() = default;

    WordDescription(EnglishWord e, Description wd)
        : englishWord{e}, description{wd}
    {
    }

    std::string toString() const
    {
        return "WordDescription{" + englishWord + "\n" + description.toString();
    }

    EnglishWord englishWord;
    Description description;
};

using WordsDescriptions = std::vector<WordDescription>;

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.description == rhs.description);
}

inline std::ostream& operator<<(std::ostream& os, const WordDescription& word)
{
    os << "\n"
       << "englishWord: " << word.englishWord << "\n"
       << "description:" << word.description << "\n";
    return os;
}
}