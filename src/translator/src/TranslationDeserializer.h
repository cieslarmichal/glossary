#pragma once

#include "TranslatedText.h"

namespace glossary::translator
{
class TranslationDeserializer
{
public:
    virtual ~TranslationDeserializer() = default;

    virtual TranslatedText deserialize(const std::string&) const = 0;
};
}
