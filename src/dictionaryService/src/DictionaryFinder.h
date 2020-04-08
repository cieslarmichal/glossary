#pragma once

#include "boost/optional.hpp"

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class DictionaryFinder
{
public:
    boost::optional<Dictionary> findDictionary(const DictionaryName&, const Dictionaries&) const;

private:
    bool dictionaryExists(const Dictionaries& dictionaries,
                          const Dictionaries::const_iterator& foundDictionary) const;
};
}