#pragma once

#include "WordSerializer.h"

class WordSerializerImpl : public WordSerializer
{
public:
    std::string serialize(const Word&) const override;
};
