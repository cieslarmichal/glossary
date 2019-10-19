#pragma once

#include "gmock/gmock.h"

#include "WordsSerializer.h"

class WordsSerializerMock : public WordsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const Words&));
    MOCK_CONST_METHOD1(deserialize, Words(const std::string&));
};
