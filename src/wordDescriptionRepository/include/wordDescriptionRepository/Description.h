#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "DefinitionWithExample.h"
#include "Sentence.h"

namespace glossary::wordDescriptionRepository
{
struct Description
{
    bool empty() const
    {
        return definitionsWithExamples.empty() && sentences.empty();
    }

    DefinitionsWithExamples definitionsWithExamples;
    Sentences sentences;
};

inline bool operator==(const Description& lhs, const Description& rhs)
{
    return (lhs.definitionsWithExamples == rhs.definitionsWithExamples && lhs.sentences == rhs.sentences);
}

inline std::string toString(const Description& description)
{
    std::string wordDescriptionAsString = "{";
    wordDescriptionAsString += "definitionsWithExamples:[";
    for (const auto& definitionAndExample : description.definitionsWithExamples)
        wordDescriptionAsString += toString(definitionAndExample) + ",";
    wordDescriptionAsString += "]";
    wordDescriptionAsString += "sentences:[";
    for (const auto& sentence : description.sentences)
        wordDescriptionAsString += sentence + ",";
    wordDescriptionAsString += "]}";
    return wordDescriptionAsString;
}

inline std::ostream& operator<<(std::ostream& os, const Description& description)
{
    return os << toString(description);
}
}
