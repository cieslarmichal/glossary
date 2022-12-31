#pragma once

#include <string>

#include "../DictionaryWord.h"

namespace glossary::dictionary
{
class GetDictionariesEnglishWordsQuery
{
public:
    virtual ~GetDictionariesEnglishWordsQuery() = default;

    virtual std::vector<std::string> getDictionariesEnglishWords() const = 0;
};
}
