#pragma once

#include <string>
#include <vector>
#include <ostream>
#include "DefinitionWithExample.h"


struct WordDescription
{
    std::string toString() const
    {
        std::string wordDescriptionAsString;

        for (const auto &definitionAndExample : definitionsWithExamples)
        {
            wordDescriptionAsString += definitionAndExample.definition + "\n";
            wordDescriptionAsString += definitionAndExample.example + "\n";
        }

        for (const auto &sentence : sentences)
        {
            wordDescriptionAsString += sentence + "\n";
        }

        wordDescriptionAsString += "\n";

        return wordDescriptionAsString;
    }

    std::vector<DefinitionWIthExample> definitionsWithExamples;
    std::vector<std::string> sentences;
};

inline bool operator==(const WordDescription& lhs, const WordDescription& rhs)
{
    return (lhs.definitionsWithExamples == rhs.definitionsWithExamples && lhs.sentences == rhs.sentences);
}

inline std::ostream & operator<<(std::ostream & os, const WordDescription& wordDescription)
{
    os << wordDescription.toString();
    return os;
}
