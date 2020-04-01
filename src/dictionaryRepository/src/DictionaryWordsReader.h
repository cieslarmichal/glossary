#pragma once

#include "Dictionary.h"
#include "boost/optional.hpp"

namespace dictionaryRepository
{
class DictionaryWordsReader
{
public:
    virtual ~DictionaryWordsReader() = default;

    virtual boost::optional<DictionaryWords> readDictionaryWords(const std::string& absolutePath) const = 0;
};
}