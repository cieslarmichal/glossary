#pragma once

#include <optional>

#include "Dictionary.h"

namespace glossary::dictionary::csvFileReading
{
class DictionaryWordsReader
{
public:
    virtual ~DictionaryWordsReader() = default;

    virtual std::optional<std::vector<DictionaryWord>>
    readDictionaryWords(const std::string& absolutePath) const = 0;
};
}