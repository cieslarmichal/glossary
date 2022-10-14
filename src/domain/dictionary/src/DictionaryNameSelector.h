#pragma once

#include "Dictionary.h"

namespace glossary::dictionary
{
class DictionaryNameSelector
{
public:
    std::vector<std::string> selectNames(const Dictionaries&) const;
};
}
