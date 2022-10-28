#pragma once

#include "gmock/gmock.h"

#include "GetDictionariesQuery.h"

namespace glossary::dictionary
{
class GetDictionariesQueryMock : public GetDictionariesQuery
{
public:
    MOCK_METHOD(std::vector<Dictionary>, getDictionaries, (), (const));
};
}
