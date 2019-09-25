#pragma once

#include "WordDescription.h"

class WordDescriptionParser
{
public:
    WordDescription parse(const std::vector<std::string> &) const;
};
