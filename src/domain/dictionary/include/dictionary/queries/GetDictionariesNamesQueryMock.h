#pragma once

#include "gmock/gmock.h"

#include "GetDictionariesNamesQuery.h"

namespace glossary::dictionary
{
class GetDictionariesNamesQueryMock : public GetDictionariesNamesQuery
{
public:
    MOCK_METHOD(std::vector<std::string>, getDictionariesNames, (), (const));
};
}
