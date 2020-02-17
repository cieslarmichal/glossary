#pragma once

#include "statisticsDb/WordStatistics.h"

namespace statisticsDb
{
class StatisticsSerializer
{
public:
    virtual ~StatisticsSerializer() = default;

    virtual std::string serialize(const Statistics&) const = 0;
    virtual Statistics deserialize(const std::string&) const = 0;
};
}