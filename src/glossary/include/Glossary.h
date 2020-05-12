#pragma once

#include <string>
#include <vector>

#include "boost/optional.hpp"

namespace glossary
{
class Glossary
{
public:
    virtual ~Glossary() = default;

    virtual bool connectionIsAvailable() const = 0;
    virtual boost::optional<std::string> getRandomPolishWord() const = 0;
    virtual boost::optional<std::string> getRandomPolishWord(const std::string& dictionaryName) const = 0;
    virtual bool verifyPolishWordTranslation(const std::string& polishWord,
                                             const std::string& englishWord) const = 0;
    virtual boost::optional<std::string> translate() const = 0;
    virtual std::vector<std::string> listDictionariesByNames() = 0;
    virtual std::vector<std::string> listDictionaryWordsFromDictionary() = 0;
    virtual void addDictionary() const = 0;
    virtual void addEnglishWordToDictionary() const = 0;
    virtual void removeDictionary() const = 0;
    virtual void removeEnglishWordFromDictionary() const = 0;
    virtual void addDictionaryFromFile() const = 0;
    virtual void updateDictionaryWordTranslationManually() const = 0;
    virtual void updateDictionaryWordTranslationAutomatically() const = 0;
    virtual void updateDictionaryTranslationsAutomatically() const = 0;
    virtual std::string getEnglishWordDescription() const = 0;
    virtual std::vector<std::string> showStatistics() const = 0;
    virtual void resetStatistics() const = 0;
};
}