#pragma once

#include <string>

struct DefinitionWIthExample
{
    std::string definition;
    std::string example;
};

inline bool operator==(const DefinitionWIthExample& lhs, const DefinitionWIthExample & rhs)
{
    return (lhs.definition == rhs.definition && lhs.example == rhs.example);
}