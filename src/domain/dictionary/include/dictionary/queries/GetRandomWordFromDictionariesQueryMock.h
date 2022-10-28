#pragma once

#include "gmock/gmock.h"

#include "GetRandomWordFromDictionariesQuery.h"

namespace glossary::dictionary
{
class GetRandomWordFromDictionariesQueryMock : public GetRandomWordFromDictionariesQuery
{
public:
    MOCK_METHOD(DictionaryWord, getRandomWord, (), (const));
};
}
