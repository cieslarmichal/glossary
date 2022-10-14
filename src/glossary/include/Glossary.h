#pragma once

#include <string>
#include <vector>

#include <optional>

#include "Dictionaries.h"
#include "DictionaryStatistics.h"
#include "ExternalServicesStatus.h"
#include "Statistics.h"
#include "WordDescription.h"

namespace glossary
{
class Glossary
{
public:
    virtual ~Glossary() = default;

    virtual ExternalServicesStatus checkConnectionToExternalServices() const = 0;
    virtual void updateTranslateApiKeyLocation(const std::string& apiKeyLocation) const = 0;
    virtual void updateWordsApiKeyLocation(const std::string& apiKeyLocation) const = 0;

    virtual std::optional<std::string> getRandomPolishWord() const = 0;
    virtual std::optional<std::string> getRandomPolishWord(const std::string&) const = 0;
    virtual bool verifyPolishWordTranslation(const std::string& polishWord,
                                             const std::string& englishWord) const = 0;
    virtual Dictionaries getDictionaries() const = 0;
    virtual std::vector<std::string> getDictionariesNames() const = 0;
    virtual std::vector<DictionaryWord> getDictionaryWords(const std::string&) const = 0;
    virtual void addDictionary(const std::string&) const = 0;
    virtual void removeDictionary(const std::string&) const = 0;
    virtual void addEnglishWordToDictionary(const std::string&, const std::string&) const = 0;
    virtual void addEnglishWordToDictionary(const std::string&, const std::string& translation,
                                            const std::string&) const = 0;
    virtual void removeEnglishWordFromDictionary(const std::string&, const std::string&) const = 0;
    virtual void addDictionaryFromFile(const std::string&,
                                       const std::string& pathToFileWithDictionaryWords) const = 0;
    virtual void updateDictionaryWordTranslationManually(const std::string&, const std::string&,
                                                         const std::string& newTranslation) const = 0;
    virtual void updateDictionaryWordTranslationAutomatically(const std::string&,
                                                              const std::string&) const = 0;
    virtual void updateDictionaryTranslationsAutomatically(const std::string&) const = 0;
    virtual WordDescription getEnglishWordDescription(const std::string&) const = 0;
    virtual std::vector<std::string> getSupportedTranslatorLanguages() const = 0;
    virtual std::optional<std::string> translate(const std::string& textToTranslate,
                                                   const std::string& sourceLanguage,
                                                   const std::string& targetLanguage) const = 0;
    virtual std::optional<DictionaryStatistics> getDictionaryStatistics(const std::string&) const = 0;
    virtual DictionariesStatistics getDictionariesStatistics() const = 0;
    virtual void resetStatistics() const = 0;
};
}
