#pragma once

#include <string>

namespace glossary::dictionary
{
class CreateDictionaryCommand
{
public:
    virtual ~CreateDictionaryCommand() = default;

    virtual void createDictionary(const std::string& dictionaryName) = 0;
};
}
