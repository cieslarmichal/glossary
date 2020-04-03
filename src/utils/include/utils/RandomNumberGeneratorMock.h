#pragma once

#include "gmock/gmock.h"

#include "RandomNumberGenerator.h"

namespace utils
{
class RandomNumberGeneratorMock : public RandomNumberGenerator
{
public:
    MOCK_METHOD2(generate, int(int rangeStart, int rangeEnd));
};
}