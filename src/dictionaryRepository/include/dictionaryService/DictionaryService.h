#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class DictionaryService
{
public:
    // TODO: addDictionaryFromFile from repo to service
    virtual ~DictionaryService() = default;

    virtual DictionaryNames getDictionaryNames() const = 0;
    virtual DictionaryWords getDictionaryWords(const DictionaryName&) const = 0;
    virtual boost::optional<DictionaryWord> getRandomDictionaryWord() const = 0;
    virtual boost::optional<DictionaryWord> getRandomDictionaryWord(const DictionaryName&) const = 0;
    virtual void addDictionary(const DictionaryName&) = 0;
    virtual void addDictionaryFromFile(const DictionaryName&, const std::string& filePath) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const DictionaryName&) = 0;
    virtual void removeDictionary(const DictionaryName&) = 0;
    virtual void removeWordFromDictionary(const std::string& word, const DictionaryName&) = 0;
};
}
