#pragma once

#include "Dictionary.h"

namespace glossary::dictionaryService
{
class DictionaryService
{
public:
    virtual ~DictionaryService() = default;

    virtual DictionaryNames getDictionaryNames() const = 0;
    virtual boost::optional<DictionaryWords> getDictionaryWords(const DictionaryName&) const = 0;
    virtual boost::optional<EnglishWords> getEnglishWords(const DictionaryName&) const = 0;
    virtual EnglishWords getEnglishWords() const = 0;
    virtual boost::optional<DictionaryWord> getRandomDictionaryWord() const = 0;
    virtual boost::optional<DictionaryWord> getRandomDictionaryWord(const DictionaryName&) const = 0;
    virtual void addDictionary(const DictionaryName&) = 0;
    virtual void addDictionaryFromFile(const DictionaryName&, const std::string& dictionaryWordsPath) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const DictionaryName&) = 0;
    virtual void removeDictionary(const DictionaryName&) = 0;
    virtual void removeWordFromDictionary(const EnglishWord&, const DictionaryName&) = 0;
};
}
