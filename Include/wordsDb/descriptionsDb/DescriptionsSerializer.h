#pragma once

#include "WordsDescriptions.h"

namespace wordsDb::descriptionsDb
{
class DescriptionsSerializer
{
public:
    virtual ~DescriptionsSerializer() = default;

    virtual std::string serialize(const Words&) const = 0;
    virtual Words deserialize(const std::string&) const = 0;
};
}
