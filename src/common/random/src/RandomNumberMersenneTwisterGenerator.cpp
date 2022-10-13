#include "RandomNumberMersenneTwisterGenerator.h"

#include <stdexcept>

namespace common::random
{
RandomNumberMersenneTwisterGenerator::RandomNumberMersenneTwisterGenerator()
    : pseudoRandomGenerator{randomDevice()}
{
}

int RandomNumberMersenneTwisterGenerator::generate(int rangeStart, int rangeEnd)
{
    if (rangeStart > rangeEnd)
    {
        throw std::invalid_argument("rangeStart value must be smaller than rangeEnd value");
    }

    std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);

    return distribution(pseudoRandomGenerator);
}
}