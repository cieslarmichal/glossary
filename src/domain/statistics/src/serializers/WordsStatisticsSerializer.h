#pragma once

#include "WordStatistics.h"

namespace glossary::statistics
{
class WordsStatisticsSerializer
{
public:
    virtual ~WordsStatisticsSerializer() = default;

    virtual std::string serialize(const std::vector<WordStatistics>&) const = 0;
    virtual std::vector<WordStatistics> deserialize(const std::string&) const = 0;
};
}
