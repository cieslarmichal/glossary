#pragma once

#include "WordRandomizer.h"

class WordMersenneTwisterRandomizer : public WordRandomizer
{
public:
    Word randomizeWord(const Words&) const override;

private:
    Words::size_type getRandomIndex(Words::size_type) const;
};