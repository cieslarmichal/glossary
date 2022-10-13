#include "SupportedThreadsCalculator.h"

#include <thread>

namespace common::concurrency
{
const unsigned SupportedThreadsCalculator::defaultAmountOfThreads{4};

unsigned int SupportedThreadsCalculator::calculate() const
{
    if (const auto amountOfSupportedThreads = getAmountOfSupportedThreads())
    {
        return *amountOfSupportedThreads;
    }

    return defaultAmountOfThreads;
}

std::optional<unsigned> SupportedThreadsCalculator::getAmountOfSupportedThreads() const
{
    const auto amountOfSupportedThreads = std::thread::hardware_concurrency();

    if (amountOfSupportedThreadsIsSpecified(amountOfSupportedThreads))
    {
        return amountOfSupportedThreads;
    }

    return std::nullopt;
}

bool SupportedThreadsCalculator::amountOfSupportedThreadsIsSpecified(unsigned amountOfThreads) const
{
    return amountOfThreads != 0;
}
}