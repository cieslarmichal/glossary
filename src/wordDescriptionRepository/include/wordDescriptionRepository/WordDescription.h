#pragma once

#include "DefinitionWithExample.h"
#include "EnglishWord.h"
#include "Sentence.h"

namespace glossary::wordDescriptionRepository
{
struct WordDescription
{
    EnglishWord englishWord;
    DefinitionsWithExamples definitionsWithExamples;
    Sentences sentences;
};

using WordsDescriptions = std::vector<WordDescription>;

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.englishWord == rhs.englishWord &&
            lhs.definitionsWithExamples == rhs.definitionsWithExamples && lhs.sentences == rhs.sentences);
}

inline bool operator<(const WordDescription& lhs, const WordDescription& rhs)
{
    return lhs.englishWord < rhs.englishWord;
}

inline std::string toString(const WordDescription& wordDescription)
{
    std::string wordDescriptionString = "{englishWord:" + wordDescription.englishWord;
    wordDescriptionString += "definitionsWithExamples:[";
    for (const auto& definitionAndExample : wordDescription.definitionsWithExamples)
        wordDescriptionString += toString(definitionAndExample) + ",";
    wordDescriptionString += "]";
    wordDescriptionString += "sentences:[";
    for (const auto& sentence : wordDescription.sentences)
        wordDescriptionString += sentence + ",";
    wordDescriptionString += "]}";
    return wordDescriptionString;
}

inline std::ostream& operator<<(std::ostream& os, const WordDescription& wordDescription)
{
    os << toString(wordDescription);
    return os;
}
}