#pragma once
#include "Translation.h"

namespace wordsDb::translationsDb
{
class TranslationSerializer
{
public:
    virtual ~TranslationSerializer() = default;

    virtual std::string serialize(const Translation&) const = 0;
    virtual Translation deserialize(const std::string&) const = 0;
};
}
