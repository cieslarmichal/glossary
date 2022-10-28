#pragma once

#include <memory>

#include "DictionaryRepository.h"
#include "DictionaryStorage.h"

namespace glossary::dictionary
{
class DefaultDictionaryRepository : public DictionaryRepository
{
public:
    explicit DefaultDictionaryRepository(std::unique_ptr<DictionaryStorage>);

    void addDictionary(const std::string& dictionaryName) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const std::string& dictionaryName) override;
    void removeDictionary(const std::string& dictionaryName) override;
    void removeWordFromDictionary(const std::string& englishWord, const std::string& dictionaryName) override;
    void changeWordTranslationFromDictionary(const std::string& englishWord, const std::string& translation,
                                             const std::string& dictionaryName) override;
    std::optional<Dictionary> getDictionary(const std::string& dictionaryName) const override;
    std::vector<Dictionary> getDictionaries() const override;
    bool containsDictionary(const std::string& dictionaryName) const override;

private:
    std::unique_ptr<DictionaryStorage> storage;
};
}
