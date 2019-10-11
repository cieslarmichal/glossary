#pragma once

#include "WordsSerializer.h"

class WordsSerializerImpl : public WordsSerializer
{
public:
    std::string serialize(const Words&) const override;
    Words deserialize(const std::string&) const override;
};
