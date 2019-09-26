#pragma once

#include <string>
#include <vector>
#include <ostream>
#include "DefinitionWithExample.h"


struct WordDescription
{
    bool operator==(const WordDescription& rhs)
    {
        return (definitionsWithExamples == rhs.definitionsWithExamples && sentences == rhs.sentences);
    }

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

inline std::ostream & operator<<(std::ostream & os, const WordDescription& wordDescription)
{
    os << wordDescription.toString();
    return os;
}
