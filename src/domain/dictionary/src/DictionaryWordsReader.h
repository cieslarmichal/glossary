#pragma once

#include <string>
#include <vector>

#include "DictionaryWord.h"

namespace glossary::dictionary
{
class DictionaryWordsReader
{
public:
    virtual ~DictionaryWordsReader() = default;

    virtual std::vector<DictionaryWord> readDictionaryWords(const std::string& absolutePath) const = 0;
};
}
