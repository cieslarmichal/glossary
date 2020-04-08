#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsRetriever.h"

namespace glossary::dictionaryService
{
class DictionaryWordsRetrieverMock : public DictionaryWordsRetriever
{
public:
    MOCK_CONST_METHOD1(retrieveDictionaryWords, boost::optional<DictionaryWords>(const DictionaryName&));
    MOCK_CONST_METHOD1(retrieveEnglishWords, boost::optional<EnglishWords>(const DictionaryName&));
    MOCK_CONST_METHOD0(retrieveEnglishWords, EnglishWords());
};
}