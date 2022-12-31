#include "RandomNumberGeneratorFactory.h"

#include "RandomNumberMersenneTwisterGenerator.h"

namespace common::random
{

std::unique_ptr<RandomNumberGenerator> RandomNumberGeneratorFactory::createRandomNumberGenerator()
{
    return std::make_unique<RandomNumberMersenneTwisterGenerator>();
}
}
