#pragma once

#include "WordDescription.h"

namespace glossary::dictionary
{
class WordsDescriptionsSerializer
{
public:
    virtual ~WordsDescriptionsSerializer() = default;

    virtual std::string serialize(const std::vector<WordDescription>&) const = 0;
    virtual std::vector<WordDescription> deserialize(const std::string&) const = 0;
};
}
