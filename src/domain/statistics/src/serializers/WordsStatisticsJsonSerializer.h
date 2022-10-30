#pragma once

#include "WordsStatisticsSerializer.h"
#include "WordStatistics.h"

namespace glossary::statistics
{
class WordsStatisticsJsonSerializer : public WordsStatisticsSerializer
{
public:
    std::string serialize(const std::vector<WordStatistics>&) const override;
    std::vector<WordStatistics> deserialize(const std::string&) const override;
};
}
