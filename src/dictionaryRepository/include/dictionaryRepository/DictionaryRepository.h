#pragma once

#include "Dictionary.h"

namespace dictionaryRepository
{
class DictionaryRepository
{
public:
    virtual ~DictionaryRepository() = default;

    virtual void addDictionary(const DictionaryName&) = 0;
    virtual void addDictionary(const Dictionary&) = 0;
    virtual void addDictionaryByPath(const std::string &absolutePath) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const DictionaryName&) = 0;
    virtual void removeDictionary(const DictionaryName&) = 0;
    virtual void removeWordFromDictionary(const std::string& englishWord, const DictionaryName&) = 0;
    virtual boost::optional<Dictionary> getDictionary(const DictionaryName&) const = 0;
    virtual Dictionaries getDictionaries() const = 0;
    virtual bool containsDictionary(const DictionaryName&) const = 0;
};
}
