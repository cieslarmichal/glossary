#pragma once

#include "TranslationDeserializer.h"
#include "nlohmann/json.hpp"

namespace translation
{

class TranslationDeserializerImpl : public TranslationDeserializer
{
public:
    std::string deserialize(const std::string&) const override;

private:
    std::string readTranslation(const nlohmann::json&) const;
};
}
