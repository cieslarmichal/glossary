#pragma once

#include "WordsRandomizer.h"

class WordsRandomizerImpl : public WordsRandomizer
{
public:
    Words randomize(const Words&) const override;

private:
    bool needToShuffle(const Words&) const;
    Words shuffleWords(const Words&) const;
};
