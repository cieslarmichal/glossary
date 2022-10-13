#pragma once

#include "Translation.h"

namespace glossary::translation
{
class TranslationsSerializer
{
public:
    virtual ~TranslationsSerializer() = default;

    virtual std::string serialize(const std::vector<Translation>&) const = 0;
    virtual std::vector<Translation> deserialize(const std::string&) const = 0;
};
}
