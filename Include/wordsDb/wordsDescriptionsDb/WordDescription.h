#pragma once

#include "Description.h"
#include "EnglishWord.h"
#include "PolishWord.h"

namespace wordsDb::wordsDescriptionsDb
{
struct WordDescription
{
    // TODO: remove polishWord
    WordDescription() = default;

    WordDescription(EnglishWord e, PolishWord p, Description wd)
        : englishWord{e}, polishWord{p}, description{wd}
    {
    }

    std::string toString() const
    {
        return "WordDescription{" + englishWord + " " + polishWord + "\n" +
               description.toString();
    }

    EnglishWord englishWord;
    PolishWord polishWord;
    Description description;
};

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.polishWord == rhs.polishWord &&
            lhs.description == rhs.description);
}

inline std::ostream& operator<<(std::ostream& os, const WordDescription& word)
{
    os << "\n"
       << "englishWord: " << word.englishWord << "\n"
       << "polishWord: " << word.polishWord << "\n"
       << "description:" << word.description << "\n";
    return os;
}
}