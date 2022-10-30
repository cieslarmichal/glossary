#pragma once

#include <string>

#include "WordDescription.h"

namespace glossary::dictionary
{
class GetWordDescriptionQuery
{
public:
    virtual ~GetWordDescriptionQuery() = default;

    virtual WordDescription getWordDescription(const std::string& englishName) const = 0;
};
}
