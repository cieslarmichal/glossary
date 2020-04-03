#pragma once

namespace utils
{
class RandomNumberGenerator
{
public:
    virtual ~RandomNumberGenerator() = default;

    virtual int generate(int rangeStart, int rangeEnd) = 0;
};
}