#pragma once

#include <string>

#include "../DictionaryWord.h"

namespace glossary::dictionary
{
class GetDictionaryEnglishWordsQuery
{
public:
    virtual ~GetDictionaryEnglishWordsQuery() = default;

    virtual std::vector<std::string> getDictionaryEnglishWords(const std::string& dictionaryName) const = 0;
};
}
