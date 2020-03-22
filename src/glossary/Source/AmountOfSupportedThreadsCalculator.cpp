#include "AmountOfSupportedThreadsCalculator.h"

#include <thread>

const unsigned AmountOfSupportedThreadsCalculator::defaultAmountOfThreads{4};

unsigned int AmountOfSupportedThreadsCalculator::calculate() const
{
    if (const auto amountOfSupportedThreads = getAmountOfSupportedThreads())
    {
        return *amountOfSupportedThreads;
    }
    return defaultAmountOfThreads;
}
boost::optional<unsigned> AmountOfSupportedThreadsCalculator::getAmountOfSupportedThreads() const
{
    const auto amountOfSupportedThreads = std::thread::hardware_concurrency();
    if (amountOfSupportedThreadsIsSpecified(amountOfSupportedThreads))
    {
        return amountOfSupportedThreads;
    }
    return boost::none;
}

bool AmountOfSupportedThreadsCalculator::amountOfSupportedThreadsIsSpecified(unsigned amountOfThreads) const
{
    return amountOfThreads != 0;
}
