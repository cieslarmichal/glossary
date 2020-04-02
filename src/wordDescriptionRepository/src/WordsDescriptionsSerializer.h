#pragma once

#include "WordDescription.h"

namespace glossary::wordDescriptionRepository
{
class WordsDescriptionsSerializer
{
public:
    virtual ~WordsDescriptionsSerializer() = default;

    virtual std::string serialize(const WordsDescriptions&) const = 0;
    virtual WordsDescriptions deserialize(const std::string&) const = 0;
};
}
