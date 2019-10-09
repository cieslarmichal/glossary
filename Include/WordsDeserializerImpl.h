#pragma once

#include "WordsDeserializer.h"

class WordsDeserializerImpl : public WordsDeserializer
{
public:
    Words deserialize(const std::string&) const override;
};
