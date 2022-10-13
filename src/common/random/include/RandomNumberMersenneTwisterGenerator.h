#pragma once

#include <random>

#include "RandomNumberGenerator.h"

namespace common::random
{
class RandomNumberMersenneTwisterGenerator : public RandomNumberGenerator
{
public:
    RandomNumberMersenneTwisterGenerator();

    int generate(int rangeStart, int rangeEnd) override;

private:
    std::random_device randomDevice;
    std::mt19937 pseudoRandomGenerator;
};
}