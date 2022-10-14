#pragma once

#include <optional>

#include "Dictionary.h"

namespace glossary::dictionary
{
class DictionaryFinder
{
public:
    std::optional<Dictionary> findDictionary(const std::string&, const Dictionaries&) const;

private:
    bool dictionaryExists(const Dictionaries& dictionaries,
                          const Dictionaries::const_iterator& foundDictionary) const;
};
}