#pragma once

#include "Words.h"

class WordRandomizer
{
public:
    virtual ~WordRandomizer() = default;

    virtual Word randomizeWord(const Words&) const = 0;
};