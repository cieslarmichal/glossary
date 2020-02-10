#pragma once

#include "TranslationDeserializer.h"
#include "nlohmann/json.hpp"

namespace translation
{

class TranslationDeserializerImpl : public TranslationDeserializer
{
public:
    TranslatedText deserialize(const std::string&) const override;

private:
    TranslatedText readTranslation(const nlohmann::json&) const;
};
}
