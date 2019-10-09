#pragma once

#include "gmock/gmock.h"

#include "DictionaryReader.h"

class DictionaryReaderMock : public DictionaryReader
{
public:
    MOCK_CONST_METHOD0(read, Dictionary());
};
