#pragma once
#include "Dictionary.h"

class DictionaryReader
{
public:
    virtual ~DictionaryReader() = default;

    virtual Dictionary read() const = 0;
};
