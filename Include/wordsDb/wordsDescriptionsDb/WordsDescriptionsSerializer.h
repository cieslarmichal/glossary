#pragma once

#include "WordsDescriptions.h"

namespace wordsDb::wordsDescriptionsDb
{
class WordsDescriptionsSerializer
{
public:
    virtual ~WordsDescriptionsSerializer() = default;

    virtual std::string serialize(const WordsDescriptions&) const = 0;
    virtual WordsDescriptions deserialize(const std::string&) const = 0;
};
}
