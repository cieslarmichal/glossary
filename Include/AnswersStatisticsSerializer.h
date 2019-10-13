#pragma once

#include <string>
#include "AnswersStatistics.h"

class AnswersStatisticsSerializer
{
public:
    virtual ~AnswersStatisticsSerializer() = default;

    virtual std::string serialize(const AnswersStatistics&) const = 0;
    virtual AnswersStatistics deserialize(const std::string&) const = 0;
};