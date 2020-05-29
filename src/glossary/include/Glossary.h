#pragma once

#include <string>
#include <vector>

#include "boost/optional.hpp"

#include "Dictionaries.h"
#include "ExternalServicesStatus.h"
#include "Statistics.h"
#include "WordDescription.h"
#include "DictionaryStatistics.h"

namespace glossary
{
class Glossary
{
public:
    virtual ~Glossary() = default;

    //TODO: check connection in gui
    virtual ExternalServicesStatus checkConnectionToExternalServices() const = 0;
    virtual boost::optional<std::string> getRandomPolishWord() const = 0;
    virtual boost::optional<std::string> getRandomPolishWord(const DictionaryName&) const = 0;
    virtual bool verifyPolishWordTranslation(const std::string& polishWord,
                                             const std::string& englishWord) const = 0;
    virtual Dictionaries getDictionaries() const = 0;
    virtual DictionaryNames getDictionariesNames() const = 0;
    virtual DictionaryWords getDictionaryWords(const DictionaryName&) const = 0;
    virtual void addDictionary(const DictionaryName&) const = 0;
    virtual void removeDictionary(const DictionaryName&) const = 0;
    virtual void addEnglishWordToDictionary(const EnglishWord&, const DictionaryName&) const = 0;
    virtual void addEnglishWordToDictionary(const EnglishWord&, const std::string& translation,
                                            const DictionaryName&) const = 0;
    virtual void removeEnglishWordFromDictionary(const EnglishWord&, const DictionaryName&) const = 0;
    virtual void addDictionaryFromFile(const DictionaryName&,
                                       const std::string& pathToFileWithDictionaryWords) const = 0;
    virtual void updateDictionaryWordTranslationManually(const DictionaryName&, const EnglishWord&,
                                                         const std::string& newTranslation) const = 0;
    virtual void updateDictionaryWordTranslationAutomatically(const DictionaryName&,
                                                              const EnglishWord&) const = 0;
    virtual void updateDictionaryTranslationsAutomatically(const DictionaryName&) const = 0;
    virtual WordDescription getEnglishWordDescription(const EnglishWord&) const = 0;
    virtual std::vector<std::string> getSupportedTranslatorLanguages() const = 0;
    virtual boost::optional<std::string> translate(const std::string& textToTranslate,
                                                   const std::string& sourceLanguage,
                                                   const std::string& targetLanguage) const = 0;
    virtual boost::optional<DictionaryStatistics> getDictionaryStatistics(const DictionaryName&) const = 0;
    virtual DictionariesStatistics getDictionariesStatistics() const = 0;
    virtual void resetStatistics() const = 0;
};
}