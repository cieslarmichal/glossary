#pragma once

#include "TranslationsSerializer.h"
#include "nlohmann/json.hpp"

namespace translationsDb
{
class TranslationsSerializerImpl : public TranslationsSerializer
{
public:
    std::string serialize(const Translations&) const override;
    Translations deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromTranslation(const Translation&) const;
    Translations readTranslations(const nlohmann::json&) const;
    Translations parseTranslations(const nlohmann::json&) const;
    bool isTranslationValid(const nlohmann::json&) const;
};
}
