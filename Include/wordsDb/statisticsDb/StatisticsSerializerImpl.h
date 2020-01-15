#pragma once

#include "StatisticsSerializer.h"
#include "nlohmann/json.hpp"

class StatisticsSerializerImpl : public StatisticsSerializer
{
public:
    std::string serialize(const AnswersStatistics&) const override;
    AnswersStatistics deserialize(const std::string&) const override;

private:
    nlohmann::json
    getJsonFromWordAnswersStatistics(const AnswersStatisticsPerWord&) const;
    AnswersStatistics readAnswersStatistics(const nlohmann::json&) const;
    AnswersStatistics parseAnswersStatistics(const nlohmann::json&) const;
    bool isWordAnswersStatisticsValid(const nlohmann::json&) const;
};
