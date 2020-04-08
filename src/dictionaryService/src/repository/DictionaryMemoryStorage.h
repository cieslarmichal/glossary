#pragma once

#include "DictionaryStorage.h"

namespace glossary::dictionaryService::repository
{
class DictionaryMemoryStorage : public DictionaryStorage
{
public:
    void addDictionary(const DictionaryName&) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const EnglishWord&, const DictionaryName&) override;
    boost::optional<Dictionary> getDictionary(const DictionaryName&) const override;
    Dictionaries getDictionaries() const override;
    bool containsDictionary(const DictionaryName&) const override;
    Dictionaries::size_type size() const override;
    bool empty() const override;

private:
    Dictionaries::const_iterator findDictionaryPosition(const DictionaryName&) const;
    DictionaryWords::const_iterator findWordInsideDictionaryPosition(const std::string& englishWord,
                                                                     const Dictionary&) const;
    bool dictionaryExists(const DictionaryName&) const;
    bool englishWordExistsInDictionary(const std::string& englishWord, const DictionaryName&) const;
    bool englishWordNotExistsInDictionary(const std::string& englishWord, const DictionaryName&) const;

    Dictionaries dictionaries;
};
}
