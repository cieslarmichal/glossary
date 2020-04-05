#pragma once

#include "boost/optional.hpp"

#include "Dictionary.h"

namespace glossary::dictionaryService::repository
{
class DictionaryStorage
{
public:
    virtual ~DictionaryStorage() = default;

    virtual void addDictionary(const DictionaryName&) = 0;
    virtual void addDictionary(const Dictionary&) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const DictionaryName&) = 0;
    virtual void removeDictionary(const DictionaryName&) = 0;
    virtual void removeWordFromDictionary(const std::string& englishWord, const DictionaryName&) = 0;
    virtual boost::optional<Dictionary> getDictionary(const DictionaryName&) const = 0;
    virtual Dictionaries getDictionaries() const = 0;
    virtual bool containsDictionary(const DictionaryName&) const = 0;
    virtual Dictionaries::size_type size() const = 0;
    virtual bool empty() const = 0;
};
}
