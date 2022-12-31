#pragma once

#include <memory>

#include "RandomNumberGenerator.h"

namespace common::random
{
class RandomNumberGeneratorFactory
{
public:
    static std::unique_ptr<RandomNumberGenerator> createRandomNumberGenerator();
};
}
