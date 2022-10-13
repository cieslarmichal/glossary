#pragma once

#include "nlohmann/json.hpp"

#include "TranslationsSerializer.h"

namespace glossary::translation
{
class TranslationsJsonSerializer : public TranslationsSerializer
{
public:
    std::string serialize(const std::vector<Translation>&) const override;
    std::vector<Translation> deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromTranslation(const Translation&) const;
    std::vector<Translation> readTranslations(const nlohmann::json&) const;
    std::vector<Translation> parseTranslations(const nlohmann::json&) const;
    bool isTranslationValid(const nlohmann::json&) const;
};
}
