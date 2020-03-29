#pragma once

#include "Dictionary.h"

namespace dictionaryRepository
{
class DictionaryReader
{
public:
    virtual ~DictionaryReader() = default;

    virtual Dictionaries readDictionaries() const = 0;
};
}