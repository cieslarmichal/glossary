#pragma once

#include "gmock/gmock.h"

#include "GetWordDescriptionQuery.h"

namespace glossary::dictionary
{
class GetWordDescriptionQueryMock : public GetWordDescriptionQuery
{
public:
    MOCK_METHOD(WordDescription, getWordDescription, (const std::string& englishName), (const));
};
}
