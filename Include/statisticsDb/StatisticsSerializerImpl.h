#pragma once

#include "StatisticsSerializer.h"
#include "nlohmann/json.hpp"

namespace statisticsDb
{

class StatisticsSerializerImpl : public StatisticsSerializer
{
public:
    std::string serialize(const Statistics&) const override;
    Statistics deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromWordStatistics(const WordStatistics&) const;
    Statistics readStatistics(const nlohmann::json&) const;
    Statistics parseStatistics(const nlohmann::json&) const;
    bool isWordStatisticsValid(const nlohmann::json&) const;
};
}
