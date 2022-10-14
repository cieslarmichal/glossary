#pragma once

#include "gmock/gmock.h"

#include "DictionaryNamesRetriever.h"

namespace glossary::dictionary
{
class DictionaryNamesRetrieverMock : public DictionaryNamesRetriever
{
public:
    MOCK_CONST_METHOD0(retrieveDictionaryNames, std::vector<std::string>());
    MOCK_CONST_METHOD1(retrieveDictionaryNamesContainingEnglishWord,
                       std::vector<std::string>(const std::string& englishWord));
    MOCK_CONST_METHOD1(retrieveDictionaryNamesContainingEnglishWordTranslation,
                       std::vector<std::string>(const std::string& englishWordTranslation));
};
}