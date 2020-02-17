#pragma once

#include "Word.h"

using namespace wordsDescriptionsDb;

class WordRandomizer
{
public:
    virtual ~WordRandomizer() = default;

    virtual Word randomizeWord(const Words&) const = 0;
};