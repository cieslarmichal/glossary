#pragma once

namespace glossary::translation
{
class TranslationDeserializer
{
public:
    virtual ~TranslationDeserializer() = default;

    virtual std::string deserialize(const std::string&) const = 0;
};
}
