#pragma once

#include "gmock/gmock.h"

#include "DictionaryService.h"

namespace glossary::dictionaryService
{
class DictionaryServiceMock : public DictionaryService
{
public:
    MOCK_CONST_METHOD0(getDictionaryNames, DictionaryNames());
    MOCK_CONST_METHOD1(getDictionaryWords, DictionaryWords(const DictionaryName&));
    MOCK_CONST_METHOD0(getRandomDictionaryWord, boost::optional<DictionaryWord>());
    MOCK_CONST_METHOD1(getRandomDictionaryWord, boost::optional<DictionaryWord>(const DictionaryName&));
    MOCK_METHOD1(getRandomDictionaryWord, DictionaryWord());
    MOCK_METHOD1(addDictionary, void(const DictionaryName&));
    MOCK_METHOD2(addDictionaryFromFile, void(const DictionaryName&, const std::string& filePath));
    MOCK_METHOD2(addWordToDictionary, void(const DictionaryWord&, const DictionaryName&));
    MOCK_METHOD1(removeDictionary, void(const DictionaryName&));
    MOCK_METHOD2(removeWordFromDictionary, void(const std::string&, const DictionaryName&));
};
}