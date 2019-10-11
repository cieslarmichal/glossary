#pragma once

#include <string>

struct DefinitionWithExample
{
    std::string definition;
    std::string example;
};

inline bool operator==(const DefinitionWithExample& lhs, const DefinitionWithExample & rhs)
{
    return (lhs.definition == rhs.definition && lhs.example == rhs.example);
}
