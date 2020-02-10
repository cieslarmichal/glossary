#pragma once

#include <string>

#include "Definition.h"
#include "Example.h"
#include "boost/optional.hpp"
#include "utils/StringHelper.h"

namespace
{
const std::string separator = ":";
}

namespace wordsDb::wordsDescriptionsDb
{
struct DefinitionWithExample
{
    std::string toString() const
    {
        std::string definitionWithExample = definition;
        if (example)
        {
            definitionWithExample += separator + *example;
        }
        return definitionWithExample;
    }

    Definition definition;
    boost::optional<Example> example;
};

inline bool operator==(const DefinitionWithExample& lhs,
                       const DefinitionWithExample& rhs)
{
    return (lhs.definition == rhs.definition && lhs.example == rhs.example);
}

inline std::ostream&
operator<<(std::ostream& os, const DefinitionWithExample& definitionWithExample)
{
    os << definitionWithExample.toString();
    return os;
}

inline DefinitionWithExample toDefinitionWithExample(const std::string& text)
{
    auto separatorIndex = text.find(separator);

    auto exampleExists = [separatorIndex]() {
        return separatorIndex != std::string::npos;
    };

    if (exampleExists())
    {
        auto definition = utils::substring(text, 0, separatorIndex);
        auto example = utils::substring(text, separatorIndex + 1, text.size());
        return DefinitionWithExample{definition, example};
    }
    else
    {
        return (DefinitionWithExample{text, boost::none});
    }
}
}
