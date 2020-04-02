#pragma once

#include "boost/optional.hpp"

namespace glossary
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