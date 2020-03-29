#pragma once

#include "Dictionary.h"

namespace dictionaryRepository
{
class DictionaryWordsReader
{
public:
    virtual ~DictionaryWordsReader() = default;

    virtual DictionaryWords readDictionaryWords(const std::string& absolutePath) const = 0;
};
}