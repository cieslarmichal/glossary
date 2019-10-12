#pragma once

#include "WordDescription.h"
#include "nlohmann/json.hpp"

class WordDescriptionSerializer
{
public:
    nlohmann::json serialize(const WordDescription&) const;
    WordDescription deserialize(const nlohmann::json &) const;
};


