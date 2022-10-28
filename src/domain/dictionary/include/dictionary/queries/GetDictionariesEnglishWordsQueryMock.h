#pragma once

#include "gmock/gmock.h"

#include "GetDictionariesEnglishWordsQuery.h"

namespace glossary::dictionary
{
class GetDictionariesEnglishWordsQueryMock : public GetDictionariesEnglishWordsQuery
{
public:
    MOCK_METHOD(std::vector<std::string>, getDictionaryWords, (), (const));
};
}
