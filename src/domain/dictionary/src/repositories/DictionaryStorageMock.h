#pragma once

#include "gmock/gmock.h"

#include "DictionaryStorage.h"

namespace glossary::dictionary
{
class DictionaryStorageMock : public DictionaryStorage
{
public:
    MOCK_METHOD1(addDictionary, void(const std::string&));
    MOCK_METHOD1(addDictionary, void(const Dictionary&));
    MOCK_METHOD2(addWordToDictionary, void(const DictionaryWord&, const std::string&));
    MOCK_METHOD1(removeDictionary, void(const std::string&));
    MOCK_METHOD2(removeWordFromDictionary, void(const std::string&, const std::string&));
    MOCK_METHOD3(changeWordTranslationFromDictionary, void(const std::string&, const std::string&, const std::string&));
    MOCK_CONST_METHOD1(getDictionary, std::optional<Dictionary>(const std::string&));
    MOCK_CONST_METHOD0(getDictionaries, std::vector<Dictionary>());
    MOCK_CONST_METHOD1(containsDictionary, bool(const std::string&));
    MOCK_CONST_METHOD0(size, std::vector<Dictionary>::size_type());
    MOCK_CONST_METHOD0(empty, bool());
};
}
