#pragma once

#include "WordsShuffler.h"

class WordsShufflerImpl : public WordsShuffler
{
public:
    WordsDescriptions shuffle(const WordsDescriptions&) const override;

private:
    bool needToShuffle(const WordsDescriptions&) const;
    WordsDescriptions shuffleWords(const WordsDescriptions&) const;
};
