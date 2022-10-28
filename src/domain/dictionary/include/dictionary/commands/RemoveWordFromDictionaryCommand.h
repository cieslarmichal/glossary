#pragma once

#include <string>

namespace glossary::dictionary
{
class RemoveWordFromDictionaryCommand
{
public:
    virtual ~RemoveWordFromDictionaryCommand() = default;

    virtual void removeWordFromDictionary(const std::string& dictionaryName, const std::string& englishWord) = 0;
};
}
