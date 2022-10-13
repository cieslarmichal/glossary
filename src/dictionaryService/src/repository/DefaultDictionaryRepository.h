#pragma once

#include <memory>

#include "DictionaryRepository.h"
#include "DictionaryStorage.h"

namespace glossary::dictionaryService::repository
{
class DefaultDictionaryRepository : public DictionaryRepository
{
public:
    explicit DefaultDictionaryRepository(std::unique_ptr<DictionaryStorage>);

    void addDictionary(const DictionaryName&) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const std::string&, const DictionaryName&) override;
    void changeWordTranslationFromDictionary(const std::string&, const std::string&,
                                             const DictionaryName&) override;
    boost::optional<Dictionary> getDictionary(const DictionaryName&) const override;
    Dictionaries getDictionaries() const override;
    bool containsDictionary(const DictionaryName&) const override;

private:
    std::unique_ptr<DictionaryStorage> storage;
};
}
