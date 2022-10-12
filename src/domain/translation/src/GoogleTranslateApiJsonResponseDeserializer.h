#pragma once

#include "nlohmann/json.hpp"

#include "TranslationDeserializer.h"

namespace glossary::translation
{
class GoogleTranslateApiJsonResponseDeserializer : public TranslationDeserializer
{
public:
    std::string deserialize(const std::string&) const override;

private:
    std::string readData(const nlohmann::json&) const;
    std::string readTranslatedText(const nlohmann::json&) const;
};
}
