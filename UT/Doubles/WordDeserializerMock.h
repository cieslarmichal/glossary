#pragma once

#include "gmock/gmock.h"

#include "WordsDeserializer.h"

class WordDeserializerMock : public WordDeserializer
{
public:
    MOCK_CONST_METHOD1(deserialize, Word(const std::string &));
};
