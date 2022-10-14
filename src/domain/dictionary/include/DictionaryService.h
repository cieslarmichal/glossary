#pragma once

#include "Dictionary.h"
#include "ObservableDictionary.h"

namespace glossary::dictionary
{
class DictionaryService : public ObservableDictionary
{
public:
    virtual ~DictionaryService() = default;

    virtual std::optional<Dictionary> getDictionary(const std::string& name) const = 0;
    virtual Dictionaries getDictionaries() const = 0;
    virtual std::vector<std::string> getDictionaryNames() const = 0;
    virtual std::vector<std::string>
    getDictionaryNamesContainingEnglishWord(const std::string& englishWord) const = 0;
    virtual std::vector<std::string>
    getDictionaryNamesContainingEnglishWordTranslation(const std::string& englishWordTranslation) const = 0;
    virtual std::optional<std::vector<DictionaryWord>>
    getDictionaryWords(const std::string& dictionaryName) const = 0;
    virtual std::optional<std::vector<std::string>>
    getEnglishWords(const std::string& dictionaryName) const = 0;
    virtual std::vector<std::string> getEnglishWords() const = 0;
    virtual std::optional<DictionaryWord> getRandomDictionaryWord() const = 0;
    virtual std::optional<DictionaryWord> getRandomDictionaryWord(const std::string&) const = 0;
    virtual void addDictionary(const std::string& dictionaryName) = 0;
    virtual void addDictionaryFromFile(const std::string& dictionaryName,
                                       const std::string& dictionaryWordsPath) = 0;
    virtual void addWordToDictionary(const DictionaryWord&, const std::string& dictionaryName) = 0;
    virtual void removeDictionary(const std::string& dictionaryName) = 0;
    virtual void removeWordFromDictionary(const std::string&, const std::string& dictionaryName) = 0;
    virtual void updateWordTranslationFromDictionary(const std::string&, const std::string& newTranslation,
                                                     const std::string& dictionaryName) = 0;
    virtual void synchronizeDictionaries() = 0;
};
}
