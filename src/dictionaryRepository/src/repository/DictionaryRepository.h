#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class DictionaryRepository
{
public:
    virtual ~DictionaryRepository() = default;

    virtual void addDictionary(const DictionaryName&) = 0;
    virtual void addDictionaryFromFile(const DictionaryName&, const std::string& dictionaryWordsPath) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const DictionaryName&) = 0;
    virtual void removeDictionary(const DictionaryName&) = 0;
    virtual void removeWordFromDictionary(const std::string& englishWord, const DictionaryName&) = 0;
    virtual boost::optional<Dictionary> getDictionary(const DictionaryName&) const = 0;
    virtual Dictionaries getDictionaries() const = 0;
    virtual bool containsDictionary(const DictionaryName&) const = 0;
};
}
