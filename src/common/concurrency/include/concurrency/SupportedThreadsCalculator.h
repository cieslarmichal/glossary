#pragma once

#include <optional>

namespace common::concurrency
{
class SupportedThreadsCalculator
{
public:
    unsigned calculate() const;

private:
    std::optional<unsigned> getAmountOfSupportedThreads() const;
    bool amountOfSupportedThreadsIsSpecified(unsigned) const;

    static const unsigned defaultAmountOfThreads;
};
}