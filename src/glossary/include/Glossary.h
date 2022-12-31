#pragma once

#include <optional>
#include <string>
#include <vector>

#include "dictionary/Dictionary.h"
#include "dictionary/WordDescription.h"
#include "DictionaryStatistics.h"

namespace glossary
{
class Glossary
{
public:
    virtual ~Glossary() = default;

    virtual std::optional<std::string> getRandomPolishWord() const = 0;
    virtual std::optional<std::string> getRandomPolishWord(const std::string&) const = 0;
    virtual bool verifyPolishWordTranslation(const std::string& polishWord, const std::string& englishWord) const = 0;
    virtual std::vector<dictionary::Dictionary> getDictionaries() const = 0;
    virtual std::vector<std::string> getDictionariesNames() const = 0;
    virtual std::vector<dictionary::DictionaryWord> getDictionaryWords(const std::string&) const = 0;
    virtual void addDictionary(const std::string&) const = 0;
    virtual void removeDictionary(const std::string&) const = 0;
    virtual void addEnglishWordToDictionary(const std::string&, const std::string&) const = 0;
    virtual void addEnglishWordToDictionary(const std::string&, const std::string& translation,
                                            const std::string&) const = 0;
    virtual void removeEnglishWordFromDictionary(const std::string&, const std::string&) const = 0;
    virtual void addDictionaryFromFile(const std::string&, const std::string& pathToFileWithDictionaryWords) = 0;
    virtual void updateDictionaryWordTranslationManually(const std::string&, const std::string&,
                                                         const std::string& newTranslation) const = 0;
    virtual void updateDictionaryWordTranslationAutomatically(const std::string&, const std::string&) const = 0;
    virtual void updateDictionaryTranslationsAutomatically(const std::string&) const = 0;
    virtual dictionary::WordDescription getEnglishWordDescription(const std::string&) const = 0;
    virtual std::vector<std::string> getSupportedTranslatorLanguages() const = 0;
    virtual std::optional<std::string> translate(const std::string& textToTranslate, const std::string& sourceLanguage,
                                                 const std::string& targetLanguage) const = 0;
    virtual std::optional<DictionaryStatistics> getDictionaryStatistics(const std::string&) const = 0;
    virtual DictionariesStatistics getDictionariesStatistics() const = 0;
    virtual void resetStatistics() const = 0;
};
}
