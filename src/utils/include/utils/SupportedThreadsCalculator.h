#pragma once

#include "boost/optional.hpp"
#include "UtilsApi.h"

namespace utils
{
class SupportedThreadsCalculator
{
public:
    UTILS_API unsigned calculate() const;

private:
    boost::optional<unsigned> getAmountOfSupportedThreads() const;
    bool amountOfSupportedThreadsIsSpecified(unsigned) const;

    static const unsigned defaultAmountOfThreads;
};
}