#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class DictionaryNameSelector
{
public:
    DictionaryNames selectNames(const Dictionaries&) const;
};
}
