#pragma once

#include "gmock/gmock.h"

#include "GoogleTranslateClient.h"

namespace glossary::translation
{
class GoogleTranslateClientMock : public GoogleTranslateClient
{
public:
    MOCK_METHOD(std::optional<std::string>, translate, (const TranslatePayload&), (const));
};
}
