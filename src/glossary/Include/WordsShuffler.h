#pragma once

#include "Word.h"

class WordsShuffler
{
public:
    virtual ~WordsShuffler() = default;

    virtual Words shuffle(const Words&) const = 0;
};
