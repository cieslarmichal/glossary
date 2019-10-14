#pragma once

#include "Words.h"

class WordsRandomizer
{
public:
    virtual ~WordsRandomizer() = default;

    virtual Words randomize(const Words&) const = 0;
};
