#pragma once

#include <optional>
#include <string>

#include "Dictionary.h"

namespace glossary::dictionary
{
class GetDictionariesQuery
{
public:
    virtual ~GetDictionariesQuery() = default;

    virtual std::vector<Dictionary> getDictionaries() const = 0;
};
}
