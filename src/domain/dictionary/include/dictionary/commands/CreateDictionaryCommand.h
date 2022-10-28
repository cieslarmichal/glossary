#pragma once

#include <optional>
#include <string>

namespace glossary::dictionary
{
class CreateDictionaryCommand
{
public:
    virtual ~CreateDictionaryCommand() = default;

    virtual void addDictionary(const std::string& dictionaryName) = 0;
};
}
