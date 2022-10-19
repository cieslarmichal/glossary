#pragma once

namespace common::random
{
class RandomNumberGenerator
{
public:
    virtual ~RandomNumberGenerator() = default;

    virtual int generate(int rangeStart, int rangeEnd) = 0;
};
}