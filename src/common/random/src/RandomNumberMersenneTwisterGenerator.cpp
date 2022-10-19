#include "RandomNumberMersenneTwisterGenerator.h"

namespace common::random
{
RandomNumberMersenneTwisterGenerator::RandomNumberMersenneTwisterGenerator()
    : pseudoRandomGenerator{randomDevice()}
{
}

int RandomNumberMersenneTwisterGenerator::generate(int rangeStart, int rangeEnd)
{
    std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);

    return distribution(pseudoRandomGenerator);
}
}