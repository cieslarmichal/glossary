#pragma once

#include "WordsShuffler.h"

class WordsShufflerImpl : public WordsShuffler
{
public:
    Words shuffle(const Words&) const override;

private:
    bool needToShuffle(const Words&) const;
    Words shuffleWords(const Words&) const;
};
