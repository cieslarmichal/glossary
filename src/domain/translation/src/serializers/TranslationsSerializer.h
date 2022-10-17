#pragma once

#include "Translation.h"

namespace glossary::translation
{
class TranslationsSerializer
{
public:
    virtual ~TranslationsSerializer() = default;

    virtual std::string serialize(const std::vector<Translation>& translations) const = 0;
    virtual std::vector<Translation> deserialize(const std::string& jsonText) const = 0;
};
}
