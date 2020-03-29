#pragma once

#include "gmock/gmock.h"

#include "DictionaryRepository.h"

namespace dictionaryRepository
{
class DictionaryRepositoryMock : public DictionaryRepository
{
public:
    MOCK_METHOD1(addDictionary, void(const DictionaryName&));
    MOCK_METHOD1(addDictionary, void(const Dictionary&));
    MOCK_METHOD1(addDictionaryByPath, void(const std::string& absolutePath));
    MOCK_METHOD2(addWordToDictionary, void(const DictionaryWord&, const DictionaryName&));
    MOCK_METHOD1(removeDictionary, void(const DictionaryName&));
    MOCK_METHOD2(removeWordFromDictionary, void(const std::string&, const DictionaryName&));
    MOCK_CONST_METHOD1(getDictionary, boost::optional<Dictionary>(const DictionaryName&));
    MOCK_CONST_METHOD0(getDictionaries, Dictionaries());
    MOCK_CONST_METHOD1(containsDictionary, bool(const DictionaryName&));
};
}