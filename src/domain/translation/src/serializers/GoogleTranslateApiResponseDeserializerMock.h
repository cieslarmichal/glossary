#pragma once

#include "gmock/gmock.h"

#include "GoogleTranslateApiResponseDeserializer.h"

namespace glossary::translation
{
class GoogleTranslateApiResponseDeserializerMock : public GoogleTranslateApiResponseDeserializer
{
public:
    MOCK_CONST_METHOD1(deserialize, GoogleTranslateApiResponse(const std::string&));
};
}