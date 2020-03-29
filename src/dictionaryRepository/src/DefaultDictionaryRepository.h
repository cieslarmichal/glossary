#pragma once

#include "DictionaryRepository.h"
#include <memory>
#include "DictionaryStorage.h"

namespace dictionaryRepository
{
class DefaultDictionaryRepository : public DictionaryRepository
{
public:
    explicit DefaultDictionaryRepository(std::unique_ptr<DictionaryStorage>);

    void addDictionary(const DictionaryName&) override;
    void addDictionary(const Dictionary&) override;
    void addDictionaryByPath(const std::string &absolutePath) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const std::string& englishWord, const DictionaryName&) override;
    boost::optional<Dictionary> getDictionary(const DictionaryName&) const override;
    Dictionaries getDictionaries() const override;
    bool containsDictionary(const DictionaryName&) const override;

private:
    std::unique_ptr<DictionaryStorage> storage;
};
}
