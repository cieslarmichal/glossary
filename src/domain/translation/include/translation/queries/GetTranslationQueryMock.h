#pragma once

#include "gmock/gmock.h"

#include "GetTranslationQuery.h"

namespace glossary::translation
{
class GetTranslationQueryMock : public GetTranslationQuery
{
public:
    MOCK_METHOD(std::optional<std::string>, getTranslation, (const GetTranslationQueryPayload&), (const));

};
}
