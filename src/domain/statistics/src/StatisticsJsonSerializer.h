#pragma once

#include "nlohmann/json.hpp"

#include "StatisticsSerializer.h"
#include "WordStatistics.h"

namespace glossary::statistics
{
class StatisticsJsonSerializer : public StatisticsSerializer
{
public:
    std::string serialize(const std::vector<WordStatistics>&) const override;
    std::vector<WordStatistics> deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromWordStatistics(const WordStatistics&) const;
    std::vector<WordStatistics> readStatistics(const nlohmann::json&) const;
    std::vector<WordStatistics> parseStatistics(const nlohmann::json&) const;
    bool isWordStatisticsValid(const nlohmann::json&) const;
};
}
