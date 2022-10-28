#pragma once

#include "gmock/gmock.h"

#include "GetDictionaryQuery.h"

namespace glossary::dictionary
{
class GetDictionaryQueryMock : public GetDictionaryQuery
{
public:
    MOCK_METHOD(std::optional<Dictionary>, getDictionary, (const std::string& dictionaryName), (const));
};
}
