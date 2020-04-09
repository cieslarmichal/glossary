#pragma once

#include "Description.h"
#include "EnglishWord.h"

namespace glossary::wordDescriptionRepository
{
struct WordDescription
{
    WordDescription() = default;
    WordDescription(EnglishWord englishWordInit, Description descriptionInit)
        : englishWord{std::move(englishWordInit)}, description{std::move(descriptionInit)}
    {
    }

    EnglishWord englishWord;
    Description description;
};

using WordsDescriptions = std::vector<WordDescription>;

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.description == rhs.description);
}

inline bool operator<(const WordDescription& lhs, const WordDescription& rhs)
{
    return lhs.englishWord < rhs.englishWord;
}

inline std::string toString(const WordDescription& wordDescription)
{
    return "{englishWord:" + wordDescription.englishWord +
           ",description:" + toString(wordDescription.description) + "}";
}

inline std::ostream& operator<<(std::ostream& os, const WordDescription& wordDescription)
{
    os << toString(wordDescription);
    return os;
}
}