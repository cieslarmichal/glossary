#pragma once

#include "boost/optional.hpp"

namespace utils
{
class SupportedThreadsCalculator
{
public:
    unsigned calculate() const;

private:
    boost::optional<unsigned> getAmountOfSupportedThreads() const;
    bool amountOfSupportedThreadsIsSpecified(unsigned) const;

    static const unsigned defaultAmountOfThreads;
};
}