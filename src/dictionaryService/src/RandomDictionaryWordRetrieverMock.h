#pragma once

#include "gmock/gmock.h"

#include "RandomDictionaryWordRetriever.h"

namespace glossary::dictionaryService
{
class RandomDictionaryWordRetrieverMock : public RandomDictionaryWordRetriever
{
public:
    MOCK_CONST_METHOD0(getRandomDictionaryWord, boost::optional<DictionaryWord>());
    MOCK_CONST_METHOD1(getRandomDictionaryWord, boost::optional<DictionaryWord>(const DictionaryName&));
};
}