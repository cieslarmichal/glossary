#pragma once

#include "boost/optional.hpp"

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class DictionaryWordSelector
{
public:
    DictionaryWords selectWords(const Dictionary&) const;
    DictionaryWords selectWords(const Dictionaries&) const;
};
}