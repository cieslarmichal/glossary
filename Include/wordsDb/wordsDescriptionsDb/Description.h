#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "DefinitionsWithExamples.h"
#include "Sentences.h"

namespace wordsDb::wordsDescriptionsDb
{
struct Description
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

inline bool operator==(const Description& lhs, const Description& rhs)
{
    return (lhs.definitionsWithExamples == rhs.definitionsWithExamples &&
            lhs.sentences == rhs.sentences);
}

inline std::ostream& operator<<(std::ostream& os,
                                const Description& wordDescription)
{
    os << wordDescription.toString();
    return os;
}
}
