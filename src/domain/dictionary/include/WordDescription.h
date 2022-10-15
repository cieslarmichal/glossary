#pragma once

#include "StlOperators.h"

namespace glossary::dictionary
{
struct WordDescription
{
    bool empty() const
    {
        return definitions.empty() && examples.empty() && synonyms.empty();
    }

    std::string englishWord;
    std::vector<std::string> definitions;
    std::vector<std::string> examples;
    std::vector<std::string> synonyms;
};

using WordsDescriptions = std::vector<WordDescription>;

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.definitions == rhs.definitions &&
            lhs.examples == rhs.examples && lhs.synonyms == rhs.synonyms);
}

inline bool operator<(const WordDescription& lhs, const WordDescription& rhs)
{
    return lhs.englishWord < rhs.englishWord;
}

inline std::string toString(const WordDescription& wordDescription)
{
    std::string wordDescriptionString = "{englishWord:" + wordDescription.englishWord;
    wordDescriptionString += "definitions:" + toStringArray(wordDescription.definitions);
    wordDescriptionString += "examples:" + toStringArray(wordDescription.examples);
    wordDescriptionString += "synonyms:" + toStringArray(wordDescription.synonyms);
    wordDescriptionString += "}";
    return wordDescriptionString;
}

inline std::ostream& operator<<(std::ostream& os, const WordDescription& wordDescription)
{
    return os << toString(wordDescription);
}
}