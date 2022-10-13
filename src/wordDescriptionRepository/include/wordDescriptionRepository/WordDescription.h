#pragma once

#include "Definition.h"
#include "Example.h"
#include "Synonym.h"

#include "utils/StlOperators.h"

namespace glossary::wordDescriptionRepository
{
struct WordDescription
{
    bool empty() const
    {
        return definitions.empty() && examples.empty() && synonyms.empty();
    }

    std::string englishWord;
    Definitions definitions;
    Examples examples;
    Synonyms synonyms;
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