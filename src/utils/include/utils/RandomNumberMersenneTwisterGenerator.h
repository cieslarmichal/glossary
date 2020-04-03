#pragma once

#include "RandomNumberGenerator.h"
#include <random>

namespace utils
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