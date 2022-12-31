#pragma once

#include <optional>
#include <string>

#include "../Dictionary.h"

namespace glossary::dictionary
{
class GetDictionariesNamesQuery
{
public:
    virtual ~GetDictionariesNamesQuery() = default;

    virtual std::vector<std::string> getDictionariesNames() const = 0;
};
}
