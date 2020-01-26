#pragma once

#include "TranslationsSerializer.h"

namespace wordsDb::translationsDb
{
class TranslationsSerializerImpl : public TranslationsSerializer
{
public:
    std::string serialize(const Translations&) const override;
    Translations deserialize(const std::string&) const override;
};
}
