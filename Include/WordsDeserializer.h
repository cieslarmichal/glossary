#pragma once

#include "Words.h"

class WordsDeserializer
{
public:
    virtual ~WordsDeserializer() = default;

    virtual Words deserialize(const std::string&) const = 0;
};
