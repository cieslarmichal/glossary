#pragma once

#include "gmock/gmock.h"

#include "RandomDictionaryWordRetriever.h"

namespace glossary::dictionary
{
class RandomDictionaryWordRetrieverMock : public RandomDictionaryWordRetriever
{
public:
    MOCK_CONST_METHOD0(getRandomDictionaryWord, std::optional<DictionaryWord>());
    MOCK_CONST_METHOD1(getRandomDictionaryWord, std::optional<DictionaryWord>(const std::string&));
};
}