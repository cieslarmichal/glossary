#pragma once

#include "gmock/gmock.h"
#include "DictionaryWordsRetriever.h"

namespace glossary::dictionaryService
{
class DictionaryWordsRetrieverMock : public DictionaryWordsRetriever
{
public:
    MOCK_CONST_METHOD1(retrieveDictionaryWords, DictionaryWords(const DictionaryName&));
};
}