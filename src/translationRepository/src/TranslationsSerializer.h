#pragma once

#include "Translation.h"

namespace translationRepository
{
class TranslationsSerializer
{
public:
    virtual ~TranslationsSerializer() = default;

    virtual std::string serialize(const Translations&) const = 0;
    virtual Translations deserialize(const std::string&) const = 0;
};
}
