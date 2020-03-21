#include "StatisticsJsonSerializer.h"

#include <iostream>

#include "boost/algorithm/cxx11/all_of.hpp"

namespace
{
constexpr auto statisticsField = "statistics";
constexpr auto englishWordField = "englishWord";
constexpr auto correctAnswersField = "correctAnswers";
constexpr auto incorrectAnswersField = "incorrectAnswers";
}

namespace statisticsDb
{
std::string StatisticsJsonSerializer::serialize(const Statistics& statistics) const
{
    nlohmann::json serialized;
    for (const auto& wordStatistics : statistics)
    {
        serialized[statisticsField].push_back(getJsonFromWordStatistics(wordStatistics));
    }
    if (serialized.empty())
    {
        return {};
    }
    return serialized.dump();
}

Statistics StatisticsJsonSerializer::deserialize(const std::string& jsonText) const
{
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

nlohmann::json StatisticsJsonSerializer::getJsonFromWordStatistics(const WordStatistics& wordStatistics) const
{
    nlohmann::json val = nlohmann::json::object();
    val[englishWordField] = wordStatistics.getEnglishWord();
    val[correctAnswersField] = wordStatistics.getAmountOfCorrectAnswers();
    val[incorrectAnswersField] = wordStatistics.getAmountOfIncorrectAnswers();
    return val;
}

Statistics StatisticsJsonSerializer::readStatistics(const nlohmann::json& json) const
{
    if (json.find(statisticsField) != json.end())
    {
        return parseStatistics(json[statisticsField]);
    }
    std::cerr << "There are no statistics stored\n";
    return {};
}

Statistics StatisticsJsonSerializer::parseStatistics(const nlohmann::json& statisticsJson) const
{
    Statistics statistics;
    for (const auto& wordStatisticsData : statisticsJson)
    {
        if (isWordStatisticsValid(wordStatisticsData))
        {
            statistics.emplace_back(WordStatistics{wordStatisticsData[englishWordField].get<std::string>(),
                                                   wordStatisticsData[correctAnswersField].get<int>(),
                                                   wordStatisticsData[incorrectAnswersField].get<int>()});
        }
        else
        {
            std::cerr << "WordStatistics does not contain all required data\n";
        }
    }
    return statistics;
}

bool StatisticsJsonSerializer::isWordStatisticsValid(const nlohmann::json& wordStatisticsJson) const
{
    const auto requiredFields = {englishWordField, correctAnswersField, incorrectAnswersField};
    auto wordStatisticsValid = boost::algorithm::all_of(requiredFields, [&](const auto& fieldName) {
        return wordStatisticsJson.find(fieldName) != wordStatisticsJson.end();
    });
    return wordStatisticsValid;
}
}