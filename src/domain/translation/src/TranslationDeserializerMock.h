#pragma once

#include "gmock/gmock.h"

#include "TranslationDeserializer.h"

namespace glossary::translation
{
class TranslationDeserializerMock : public TranslationDeserializer
{
public:
    MOCK_CONST_METHOD1(deserialize, std::string(const std::string&));
};
}