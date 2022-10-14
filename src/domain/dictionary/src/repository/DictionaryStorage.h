#pragma once

#include <optional>

#include "Dictionary.h"

namespace glossary::dictionary::repository
{
class DictionaryStorage
{
public:
    virtual ~DictionaryStorage() = default;

    virtual void addDictionary(const std::string&) = 0;
    virtual void addDictionary(const Dictionary&) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const std::string&) = 0;
    virtual void removeDictionary(const std::string&) = 0;
    virtual void removeWordFromDictionary(const std::string&, const std::string&) = 0;
    virtual void changeWordTranslationFromDictionary(const std::string&, const std::string&,
                                                     const std::string&) = 0;
    virtual std::optional<Dictionary> getDictionary(const std::string&) const = 0;
    virtual Dictionaries getDictionaries() const = 0;
    virtual bool containsDictionary(const std::string&) const = 0;
    virtual Dictionaries::size_type size() const = 0;
    virtual bool empty() const = 0;
};
}
