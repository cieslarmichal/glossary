#pragma once

#include "nlohmann/json.hpp"

#include "TranslationDeserializer.h"

namespace translator
{
class TranslationJsonDeserializer : public TranslationDeserializer
{
public:
    TranslatedText deserialize(const std::string&) const override;

private:
    TranslatedText readTranslation(const nlohmann::json&) const;
};
}
