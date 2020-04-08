#pragma once

#include "nlohmann/json.hpp"

#include "TranslationDeserializer.h"

namespace glossary::translator
{
class GoogleTranslateApiJsonResponseDeserializer : public TranslationDeserializer
{
public:
    TranslatedText deserialize(const std::string&) const override;

private:
    TranslatedText readData(const nlohmann::json&) const;
    TranslatedText readTranslatedText(const nlohmann::json&) const;
};
}
