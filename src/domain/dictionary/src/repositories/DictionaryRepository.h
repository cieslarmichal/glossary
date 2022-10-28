#pragma once

#include "Dictionary.h"

namespace glossary::dictionary
{
class DictionaryRepository
{
public:
    virtual ~DictionaryRepository() = default;

    virtual void addDictionary(const std::string& dictionaryName) = 0;
    virtual void addDictionary(const Dictionary&) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const std::string& dictionaryName) = 0;
    virtual void removeDictionary(const std::string& dictionaryName) = 0;
    virtual void removeWordFromDictionary(const std::string& englishWord, const std::string& dictionaryName) = 0;
    virtual void changeWordTranslationFromDictionary(const std::string& englishWord, const std::string& translation,
                                                     const std::string& dictionaryName) = 0;
    virtual std::optional<Dictionary> getDictionary(const std::string& dictionaryName) const = 0;
    virtual std::vector<Dictionary> getDictionaries() const = 0;
    virtual bool containsDictionary(const std::string& dictionaryName) const = 0;
};
}
