#pragma once

#include "gmock/gmock.h"

#include "GetDictionaryEnglishWordsQuery.h"

namespace glossary::dictionary
{
class GetDictionaryEnglishWordsQueryMock : public GetDictionaryEnglishWordsQuery
{
public:
    MOCK_METHOD(std::vector<std::string>, getDictionaryWords, (const std::string&), (const));
};
}
