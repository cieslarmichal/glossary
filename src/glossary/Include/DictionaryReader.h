#pragma once

#include "Dictionary.h"

class DictionaryReader
{
public:
    virtual ~DictionaryReader() = default;

    virtual Dictionaries readDictionaries() const = 0;
};
