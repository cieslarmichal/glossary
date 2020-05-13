#pragma once

#include <string>
#include <vector>

#include "boost/optional.hpp"

#include "ExternalServicesAvailabilityStatus.h"

namespace glossary
{
class Glossary
{
public:
    virtual ~Glossary() = default;

    virtual ExternalServicesAvailabilityStatus checkConnectionToExternalServices() const = 0;
    virtual boost::optional<std::string> getRandomPolishWord() const = 0;
    virtual boost::optional<std::string> getRandomPolishWord(const std::string& dictionaryName) const = 0;
    virtual bool verifyPolishWordTranslation(const std::string& polishWord,
                                             const std::string& englishWord) const = 0;
    virtual std::vector<std::string> listDictionariesNames() = 0;
    virtual std::vector<std::string> listDictionaryWordsFromDictionary(const std::string& dictionaryName) = 0;
    virtual void addDictionary(const std::string& dictionaryName) const = 0;
    virtual void removeDictionary(const std::string& dictionaryName) const = 0;
    virtual void addEnglishWordToDictionary(const std::string& englishWord,
                                            const std::string& dictionaryName) const = 0;
    virtual void removeEnglishWordFromDictionary(const std::string& englishWord,
                                                 const std::string& dictionaryName) const = 0;
    virtual void addDictionaryFromFile(const std::string& dictionaryName,
                                       const std::string& pathToFileWithDictionaryWords) const = 0;
    virtual void updateDictionaryWordTranslationManually(const std::string& dictionaryName,
                                                         const std::string& englishWord,
                                                         const std::string& newTranslation) const = 0;
    virtual void updateDictionaryWordTranslationAutomatically(const std::string& dictionaryName,
                                                              const std::string& englishWord) const = 0;
    virtual void updateDictionaryTranslationsAutomatically(const std::string& dictionaryName) const = 0;
    virtual std::string getEnglishWordDescription(const std::string& englishWord) const = 0;
    virtual std::vector<std::string> getSupportedTranslatorLanguages() const = 0;
    virtual boost::optional<std::string> translate(const std::string& textToTranslate,
                                                   const std::string& sourceLanguage,
                                                   const std::string& targetLanguage) const = 0;
    virtual std::vector<std::string> showStatistics() const = 0;
    virtual void resetStatistics() const = 0;
};
}