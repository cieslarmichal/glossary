#pragma once

#include <string>

namespace glossary::dictionary
{
class RemoveDictionaryCommand
{
public:
    virtual ~RemoveDictionaryCommand() = default;

    virtual void removeDictionary(const std::string& dictionaryName) = 0;
};
}
