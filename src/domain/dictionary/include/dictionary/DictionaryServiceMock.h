#pragma once

#include "gmock/gmock.h"

#include "DictionaryService.h"

namespace glossary::dictionary
{
class DictionaryServiceMock : public DictionaryService
{
public:
    MOCK_CONST_METHOD1(getDictionary, std::optional<Dictionary>(const std::string&));
    MOCK_CONST_METHOD0(getDictionaries, Dictionaries());
    MOCK_CONST_METHOD0(getDictionaryNames, std::vector<std::string>());
    MOCK_CONST_METHOD1(getDictionaryWords, std::optional<std::vector<DictionaryWord>>(const std::string&));
    MOCK_CONST_METHOD1(getEnglishWords, std::optional<std::vector<std::string>>(const std::string&));
    MOCK_CONST_METHOD0(getEnglishWords, std::vector<std::string>());
    MOCK_CONST_METHOD0(getRandomDictionaryWord, std::optional<DictionaryWord>());
    MOCK_CONST_METHOD1(getRandomDictionaryWord, std::optional<DictionaryWord>(const std::string&));
    MOCK_METHOD1(addDictionary, void(const std::string&));
    MOCK_METHOD2(addDictionaryFromFile, void(const std::string&, const std::string& filePath));
    MOCK_METHOD2(addWordToDictionary, void(const DictionaryWord&, const std::string&));
    MOCK_METHOD1(removeDictionary, void(const std::string&));
    MOCK_METHOD2(removeWordFromDictionary, void(const std::string&, const std::string&));
    MOCK_METHOD3(updateWordTranslationFromDictionary, void(const std::string&, const std::string&, const std::string&));
    MOCK_METHOD0(synchronizeDictionaries, void());
    MOCK_METHOD1(registerObserver, void(DictionaryObserver*));
    MOCK_METHOD1(removeObserver, void(DictionaryObserver*));
    MOCK_METHOD1(notifyObservers, void(const std::vector<std::string>&));
};
}
