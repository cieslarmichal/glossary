#pragma once

#include "Word.h"

class WordSerializer
{
public:
    //TODO: JsonCpp
    virtual ~WordSerializer() = default;

    virtual std::string serialize(const Word&) const = 0;
};
