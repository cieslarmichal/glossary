#pragma once

#include <random>

#include "RandomNumberGenerator.h"
#include "UtilsApi.h"

namespace utils
{
class RandomNumberMersenneTwisterGenerator : public RandomNumberGenerator
{
public:
    UTILS_API RandomNumberMersenneTwisterGenerator();

    UTILS_API int generate(int rangeStart, int rangeEnd) override;

private:
    std::random_device randomDevice;
    std::mt19937 pseudoRandomGenerator;
};
}