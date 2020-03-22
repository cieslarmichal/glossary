#pragma once

#include "Words.h"

class WordRandomizer
{
public:
    virtual ~WordRandomizer() = default;

    virtual Word randomizeWord(const UniqueWords&) const = 0;
};