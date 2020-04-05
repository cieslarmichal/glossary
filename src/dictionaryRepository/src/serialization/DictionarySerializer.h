#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService
{
// TODO: add namespaces in directories
class DictionarySerializer
{
public:
    virtual ~DictionarySerializer() = default;

    virtual std::string serialize(const Dictionaries&) const = 0;
    virtual Dictionaries deserialize(const std::string&) const = 0;
};
}
