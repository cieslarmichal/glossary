#pragma once

#include "gmock/gmock.h"

#include "TranslationDeserializer.h"

namespace translator
{

class TranslationDeserializerMock : public TranslationDeserializer
{
public:
    MOCK_CONST_METHOD1(deserialize, TranslatedText(const std::string&));
};
}