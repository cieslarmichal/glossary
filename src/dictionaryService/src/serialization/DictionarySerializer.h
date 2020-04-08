#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService::serialization
{
class DictionarySerializer
{
public:
    virtual ~DictionarySerializer() = default;

    virtual std::string serialize(const Dictionaries&) const = 0;
    virtual Dictionaries deserialize(const std::string&) const = 0;
};
}
