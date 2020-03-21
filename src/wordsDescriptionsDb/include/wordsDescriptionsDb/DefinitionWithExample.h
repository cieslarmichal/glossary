#pragma once

#include "boost/optional.hpp"
#include "boost/optional/optional_io.hpp"

#include "Definition.h"
#include "Example.h"

namespace wordsDescriptionsDb
{
struct DefinitionWithExample
{
    Definition definition;
    boost::optional<Example> example;
};

using DefinitionsWithExamples = std::vector<DefinitionWithExample>;

inline bool operator==(const DefinitionWithExample& lhs, const DefinitionWithExample& rhs)
{
    return (lhs.definition == rhs.definition && lhs.example == rhs.example);
}

inline bool operator<(const DefinitionWithExample& lhs, const DefinitionWithExample& rhs)
{
    return (lhs.definition < rhs.definition && lhs.example < rhs.example);
}

inline std::string toString(const DefinitionWithExample& definitionWithExample)
{
    std::string defWithExample = "{" + definitionWithExample.definition;
    if (definitionWithExample.example)
    {
        defWithExample += ":" + *definitionWithExample.example;
    }
    defWithExample += "}";
    return defWithExample;
}

inline std::ostream& operator<<(std::ostream& os, const DefinitionWithExample& definitionWithExample)
{
    os << toString(definitionWithExample);
    return os;
}
}
