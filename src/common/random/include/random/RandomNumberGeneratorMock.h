#pragma once

#include "gmock/gmock.h"

#include "RandomNumberGenerator.h"

namespace common::random
{
class RandomNumberGeneratorMock : public RandomNumberGenerator
{
public:
    MOCK_METHOD(int, generate, (int rangeStart, int rangeEnd), ());
};
}
