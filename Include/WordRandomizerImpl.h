#pragma once

#include "WordRandomizer.h"

class WordRandomizerImpl : public WordRandomizer
{
public:
    WordDescription randomizeWord(const WordsDescriptions&) const override;

private:
    WordsDescriptions::size_type
        getRandomIndex(WordsDescriptions::size_type) const;
};