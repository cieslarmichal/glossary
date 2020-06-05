#pragma once

#include "gmock/gmock.h"

#include "DictionaryNamesRetriever.h"

namespace glossary::dictionaryService
{
class DictionaryNamesRetrieverMock : public DictionaryNamesRetriever
{
public:
    MOCK_CONST_METHOD0(retrieveDictionaryNames, DictionaryNames());
    MOCK_CONST_METHOD1(retrieveDictionaryNamesContainingEnglishWord,
                       DictionaryNames(const std::string& englishWord));
    MOCK_CONST_METHOD1(retrieveDictionaryNamesContainingEnglishWordTranslation,
                       DictionaryNames(const std::string& englishWordTranslation));
};
}