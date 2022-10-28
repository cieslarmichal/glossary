#pragma once

#include <string>

#include "DictionaryWord.h"

namespace glossary::dictionary
{
class AddWordToDictionaryCommand
{
public:
    virtual ~AddWordToDictionaryCommand() = default;

    virtual void addWordToDictionary(const std::string& dictionaryName, const DictionaryWord&) = 0;
};
}
