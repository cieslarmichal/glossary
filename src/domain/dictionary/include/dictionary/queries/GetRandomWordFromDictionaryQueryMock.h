#pragma once

#include "gmock/gmock.h"

#include "GetRandomWordFromDictionaryQuery.h"

namespace glossary::dictionary
{
class GetRandomWordFromDictionaryQueryMock : public GetRandomWordFromDictionaryQuery
{
public:
    MOCK_METHOD(DictionaryWord, getRandomWord, (const std::string& dictionaryName), (const));
};
}
