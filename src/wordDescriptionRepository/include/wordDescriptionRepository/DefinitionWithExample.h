#pragma once

#include <vector>

#include "Definition.h"
#include "Example.h"

namespace glossary::wordDescriptionRepository
{
struct DefinitionWithExample
{
    Definition definition;
    std::vector<Example> examples;
};

using DefinitionsWithExamples = std::vector<DefinitionWithExample>;

inline bool operator==(const DefinitionWithExample& lhs, const DefinitionWithExample& rhs)
{
    return (lhs.definition == rhs.definition && lhs.examples == rhs.examples);
}

inline bool operator<(const DefinitionWithExample& lhs, const DefinitionWithExample& rhs)
{
    return (lhs.definition < rhs.definition && lhs.examples < rhs.examples);
}

inline std::string toString(const DefinitionWithExample& definitionWithExample)
{
    std::string definitionWithExampleString = "{definition:" + definitionWithExample.definition;
    definitionWithExampleString += "examples:[";
    for (const auto& example : definitionWithExample.examples)
        definitionWithExampleString += example + ",";
    definitionWithExampleString += "]}";
    return definitionWithExampleString;
}

inline std::ostream& operator<<(std::ostream& os, const DefinitionWithExample& definitionWithExample)
{
    return os << toString(definitionWithExample);
}
}
