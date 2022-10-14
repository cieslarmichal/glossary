#pragma once

#include <memory>

#include "DictionaryRepository.h"
#include "DictionaryStorage.h"

namespace glossary::dictionary::repository
{
class DefaultDictionaryRepository : public DictionaryRepository
{
public:
    explicit DefaultDictionaryRepository(std::unique_ptr<DictionaryStorage>);

    void addDictionary(const std::string&) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const std::string&) override;
    void removeDictionary(const std::string&) override;
    void removeWordFromDictionary(const std::string&, const std::string&) override;
    void changeWordTranslationFromDictionary(const std::string&, const std::string&,
                                             const std::string&) override;
    std::optional<Dictionary> getDictionary(const std::string&) const override;
    Dictionaries getDictionaries() const override;
    bool containsDictionary(const std::string&) const override;

private:
    std::unique_ptr<DictionaryStorage> storage;
};
}
