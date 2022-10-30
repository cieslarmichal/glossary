#pragma once

#include <vector>

#include "WordStatistics.h"

namespace glossary::statistics
{
class GetWordsStatisticsQuery
{
public:
    virtual ~GetWordsStatisticsQuery() = default;

    virtual std::vector<WordStatistics> getWordsStatistics() = 0;
};
}
