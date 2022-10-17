#pragma once

#include "TranslationsSerializer.h"

namespace glossary::translation
{
class TranslationsJsonSerializer : public TranslationsSerializer
{
public:
    std::string serialize(const std::vector<Translation>& translations) const override;
    std::vector<Translation> deserialize(const std::string& json) const override;
};
}
