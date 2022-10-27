#pragma once

#include "DictionaryStorage.h"

namespace glossary::dictionary
{
class DictionaryMemoryStorage : public DictionaryStorage
{
public:
    void addDictionary(const std::string&) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const std::string&) override;
    void removeDictionary(const std::string&) override;
    void removeWordFromDictionary(const std::string&, const std::string&) override;
    void changeWordTranslationFromDictionary(const std::string&, const std::string&, const std::string&) override;
    std::optional<Dictionary> getDictionary(const std::string&) const override;
    std::vector<Dictionary> getDictionaries() const override;
    bool containsDictionary(const std::string&) const override;
    std::vector<Dictionary>::size_type size() const override;
    bool empty() const override;

private:
    std::vector<Dictionary>::const_iterator findDictionaryPosition(const std::string&) const;
    std::vector<DictionaryWord>::const_iterator findWordInsideDictionaryPosition(const std::string& englishWord,
                                                                                 const Dictionary&) const;
    bool dictionaryExists(const std::string&) const;
    bool englishWordExistsInDictionary(const std::string& englishWord, const std::string&) const;
    bool englishWordNotExistsInDictionary(const std::string& englishWord, const std::string&) const;

    std::vector<Dictionary> dictionaries;
};
}
