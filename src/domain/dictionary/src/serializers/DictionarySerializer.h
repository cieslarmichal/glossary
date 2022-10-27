#pragma once

#include "Dictionary.h"

namespace glossary::dictionary
{
class DictionarySerializer
{
public:
    virtual ~DictionarySerializer() = default;

    virtual std::string serialize(const std::vector<Dictionary>&) const = 0;
    virtual std::vector<Dictionary> deserialize(const std::string&) const = 0;
};
}
