#pragma once

#include "gmock/gmock.h"

#include "WordSerializer.h"

class WordSerializerMock : public WordSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const Word &));
};
