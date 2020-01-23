#pragma once

#include <string>

#include "Statistics.h"

namespace wordsDb::statisticsDb
{
class StatisticsSerializer
{
public:
    virtual ~StatisticsSerializer() = default;

    virtual std::string serialize(const Statistics&) const = 0;
    virtual Statistics deserialize(const std::string&) const = 0;
};
}