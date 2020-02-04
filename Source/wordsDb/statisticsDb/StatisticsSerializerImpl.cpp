#include "wordsDb/statisticsDb/StatisticsSerializerImpl.h"

#include <iostream>

#include "boost/algorithm/cxx11/any_of.hpp"

namespace
{
constexpr auto statisticsField = "statistics";
constexpr auto englishWordField = "englishWord";
constexpr auto correctAnswersField = "correctAnswers";
constexpr auto incorrectAnswersField = "incorrectAnswers";
}

namespace wordsDb::statisticsDb
{
std::string
StatisticsSerializerImpl::serialize(const Statistics& statistics) const
{
    nlohmann::json serialized;
    for (const auto& wordStatistics : statistics)
    {
        serialized[statisticsField].push_back(
            getJsonFromWordStatistics(wordStatistics));
    }
    if (serialized.empty())
    {
        return {};
    }
    return serialized.dump();
}

Statistics
StatisticsSerializerImpl::deserialize(const std::string& jsonText) const
{
    if (jsonText.empty())
    {
        return {};
    }

    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readStatistics(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse statistics:" << e.what();
    }
    return {};
}

nlohmann::json StatisticsSerializerImpl::getJsonFromWordStatistics(
    const WordStatistics& wordStatistics) const
{
    nlohmann::json val = nlohmann::json::object();
    val[englishWordField] = wordStatistics.englishWord;
    val[correctAnswersField] = wordStatistics.correctAnswers;
    val[incorrectAnswersField] = wordStatistics.incorrectAnswers;
    return val;
}

Statistics
StatisticsSerializerImpl::readStatistics(const nlohmann::json& json) const
{
    if (json.find(statisticsField) != json.end())
    {
        return parseStatistics(json[statisticsField]);
    }
    std::cerr << "There are no statistics stored\n";
    return {};
}

Statistics StatisticsSerializerImpl::parseStatistics(
    const nlohmann::json& statisticsJson) const
{
    Statistics statistics;
    for (const auto& wordStatisticsData : statisticsJson)
    {
        if (isWordStatisticsValid(wordStatisticsData))
        {
            statistics.emplace_back(
                WordStatistics{wordStatisticsData[englishWordField],
                               wordStatisticsData[correctAnswersField],
                               wordStatisticsData[incorrectAnswersField]});
        }
        else
        {
            std::cerr << "wordStatistics does not contain all required data\n";
        }
    }
    return statistics;
}

bool StatisticsSerializerImpl::isWordStatisticsValid(
    const nlohmann::json& wordStatisticsJson) const
{
    const auto requiredFields = {englishWordField, correctAnswersField,
                                 incorrectAnswersField};
    auto wordInvalid =
        boost::algorithm::any_of(requiredFields, [&](const auto& fieldName) {
            return wordStatisticsJson.find(fieldName) ==
                   wordStatisticsJson.end();
        });
    return !wordInvalid;
}
}