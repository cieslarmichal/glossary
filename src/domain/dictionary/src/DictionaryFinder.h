#pragma once

#include <optional>

#include "Dictionary.h"

namespace glossary::dictionary
{
class DictionaryFinder
{
public:
    std::optional<Dictionary> findDictionary(const std::string&, const std::vector<Dictionary>&) const;

private:
    bool dictionaryExists(const std::vector<Dictionary>& dictionaries,
                          const std::vector<Dictionary>::const_iterator& foundDictionary) const;
};
}
