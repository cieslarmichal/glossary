#pragma once

#include "Words.h"

class WordsSerializer
{
public:
    //TODO: JsonCpp
    virtual ~WordsSerializer() = default;

    virtual std::string serialize(const Words&) const = 0;
    virtual Words deserialize(const std::string&) const = 0;
};
