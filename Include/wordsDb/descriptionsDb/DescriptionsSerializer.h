#pragma once

#include "WordsDescriptions.h"

namespace wordsDb::descriptionsDb
{
class DescriptionsSerializer
{
public:
    virtual ~DescriptionsSerializer() = default;

    virtual std::string serialize(const WordsDescriptions&) const = 0;
    virtual WordsDescriptions deserialize(const std::string&) const = 0;
};
}
