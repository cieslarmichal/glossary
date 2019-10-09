#pragma once

#include "gmock/gmock.h"

#include "DictionaryAvailabilityHandler.h"

class DictionaryAvailabilityHandlerMock : public DictionaryAvailabilityHandler
{
public:
    MOCK_CONST_METHOD0(read, DictionaryAvailability());
    MOCK_CONST_METHOD1(add, void(const WordAvailability&));
};
