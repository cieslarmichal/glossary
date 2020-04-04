#include "utils/SupportedThreadsCalculator.h"

#include <thread>

namespace utils
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
boost::optional<unsigned> SupportedThreadsCalculator::getAmountOfSupportedThreads() const
{
    const auto amountOfSupportedThreads = std::thread::hardware_concurrency();
    if (amountOfSupportedThreadsIsSpecified(amountOfSupportedThreads))
    {
        return amountOfSupportedThreads;
    }
    return boost::none;
}

bool SupportedThreadsCalculator::amountOfSupportedThreadsIsSpecified(unsigned amountOfThreads) const
{
    return amountOfThreads != 0;
}
}