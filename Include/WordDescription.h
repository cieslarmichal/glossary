#pragma once

#include <string>
#include <vector>
#include <ostream>
#include "DefinitionsWithExamples.h"
#include "Sentences.h"


struct WordDescription
{
    std::string toString() const
    {
        std::string wordDescriptionAsString;

        for (const auto& definitionAndExample : definitionsWithExamples)
        {
            wordDescriptionAsString += definitionAndExample.toString() + "\n";
        }

        for (const auto& sentence : sentences)
        {
            wordDescriptionAsString += sentence + "\n";
        }

        return wordDescriptionAsString;
    }

    bool empty() const
    {
        return definitionsWithExamples.empty() && sentences.empty();
    }

    DefinitionsWithExamples definitionsWithExamples;
    Sentences sentences;
};

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.definitionsWithExamples == rhs.definitionsWithExamples && lhs.sentences == rhs.sentences);
}

inline std::ostream& operator<<(std::ostream& os, const WordDescription& wordDescription)
{
    os << wordDescription.toString();
    return os;
}

