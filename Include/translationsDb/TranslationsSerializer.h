#pragma once
#include "Translations.h"

namespace translationsDb
{
class TranslationsSerializer
{
public:
    virtual ~TranslationsSerializer() = default;

    virtual std::string serialize(const Translations&) const = 0;
    virtual Translations deserialize(const std::string&) const = 0;
};
}
