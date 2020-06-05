#pragma once

#include "gmock/gmock.h"

#include "DictionaryService.h"

namespace glossary::dictionaryService
{
class DictionaryServiceMock : public DictionaryService
{
public:
    MOCK_CONST_METHOD1(getDictionary, boost::optional<Dictionary>(const DictionaryName&));
    MOCK_CONST_METHOD0(getDictionaries, Dictionaries());
    MOCK_CONST_METHOD0(getDictionaryNames, DictionaryNames());
    MOCK_CONST_METHOD1(getDictionaryNamesContainingEnglishWord,
                       DictionaryNames(const std::string& englishWord));
    MOCK_CONST_METHOD1(getDictionaryNamesContainingEnglishWordTranslation,
                       DictionaryNames(const std::string& englishWordTranslation));
    MOCK_CONST_METHOD1(getDictionaryWords, boost::optional<DictionaryWords>(const DictionaryName&));
    MOCK_CONST_METHOD1(getEnglishWords, boost::optional<EnglishWords>(const DictionaryName&));
    MOCK_CONST_METHOD0(getEnglishWords, EnglishWords());
    MOCK_CONST_METHOD0(getRandomDictionaryWord, boost::optional<DictionaryWord>());
    MOCK_CONST_METHOD1(getRandomDictionaryWord, boost::optional<DictionaryWord>(const DictionaryName&));
    MOCK_METHOD1(addDictionary, void(const DictionaryName&));
    MOCK_METHOD2(addDictionaryFromFile, void(const DictionaryName&, const std::string& filePath));
    MOCK_METHOD2(addWordToDictionary, void(const DictionaryWord&, const DictionaryName&));
    MOCK_METHOD1(removeDictionary, void(const DictionaryName&));
    MOCK_METHOD2(removeWordFromDictionary, void(const EnglishWord&, const DictionaryName&));
    MOCK_METHOD3(updateWordTranslationFromDictionary,
                 void(const EnglishWord&, const std::string&, const DictionaryName&));
    MOCK_METHOD0(synchronizeDictionaries, void());
    MOCK_METHOD1(registerObserver, void(DictionaryObserver*));
    MOCK_METHOD1(removeObserver, void(DictionaryObserver*));
    MOCK_METHOD1(notifyObservers, void(const EnglishWords&));
};
}