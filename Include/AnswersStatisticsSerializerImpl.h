#pragma once

#include "AnswersStatisticsSerializer.h"
#include "nlohmann/json.hpp"


class AnswersStatisticsSerializerImpl : public AnswersStatisticsSerializer
{
public:
    //TODO: change answersStatistics to wordsAnswersStatistics! bad names
    std::string serialize(const AnswersStatistics&) const override;
    AnswersStatistics deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromWordAnswersStatistics(const WordAnswersStatistics&) const;
    AnswersStatistics readAnswersStatistics(const nlohmann::json&) const;
    AnswersStatistics parseAnswersStatistics(const nlohmann::json&) const;
    bool isWordAnswersStatisticsValid(const nlohmann::json&) const;
};