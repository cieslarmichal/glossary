#pragma once

#include <string>

#include "Statistics.h"

namespace wordsDb::statisticsDb
{
class StatisticsSerializer
{
public:
    virtual ~StatisticsSerializer() = default;

    virtual std::string serialize(const AnswersStatistics&) const = 0;
    virtual AnswersStatistics deserialize(const std::string&) const = 0;
};
}