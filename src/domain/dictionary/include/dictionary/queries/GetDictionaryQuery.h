#pragma once

#include <optional>
#include <string>

#include "../Dictionary.h"

namespace glossary::dictionary
{
class GetDictionaryQuery
{
public:
    virtual ~GetDictionaryQuery() = default;

    virtual std::optional<Dictionary> getDictionary(const std::string& dictionaryName) const = 0;
};
}
