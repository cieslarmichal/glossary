#include "StatisticsSerializerImpl.h"

#include "boost/algorithm/cxx11/all_of.hpp"
#include "plog/Log.h"

namespace
{
constexpr auto statisticsField = "statistics";
constexpr auto englishWordField = "englishWord";
constexpr auto correctAnswersField = "correctAnswers";
constexpr auto incorrectAnswersField = "incorrectAnswers";
}

namespace statisticsDb
{
std::string StatisticsSerializerImpl::serialize(const Statistics& statistics) const
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

Statistics StatisticsSerializerImpl::deserialize(const std::string& jsonText) const
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
        LOG_WARNING << "Unable to parse statistics:" << e.what();
    }
    return {};
}

nlohmann::json StatisticsSerializerImpl::getJsonFromWordStatistics(const WordStatistics& wordStatistics) const
{
    nlohmann::json val = nlohmann::json::object();
    val[englishWordField] = wordStatistics.englishWord;
    val[correctAnswersField] = wordStatistics.correctAnswers;
    val[incorrectAnswersField] = wordStatistics.incorrectAnswers;
    return val;
}

Statistics StatisticsSerializerImpl::readStatistics(const nlohmann::json& json) const
{
    if (json.find(statisticsField) != json.end())
    {
        return parseStatistics(json[statisticsField]);
    }
    LOG_WARNING << "There are no statistics stored\n";
    return {};
}

Statistics StatisticsSerializerImpl::parseStatistics(const nlohmann::json& statisticsJson) const
{
    Statistics statistics;
    for (const auto& wordStatisticsData : statisticsJson)
    {
        if (isWordStatisticsValid(wordStatisticsData))
        {
            statistics.emplace_back(WordStatistics{wordStatisticsData[englishWordField],
                                                   wordStatisticsData[correctAnswersField],
                                                   wordStatisticsData[incorrectAnswersField]});
        }
        else
        {
            LOG_WARNING << "WordStatistics does not contain all required data\n";
        }
    }
    return statistics;
}

bool StatisticsSerializerImpl::isWordStatisticsValid(const nlohmann::json& wordStatisticsJson) const
{
    const auto requiredFields = {englishWordField, correctAnswersField, incorrectAnswersField};
    auto wordStatisticsValid = boost::algorithm::all_of(requiredFields, [&](const auto& fieldName) {
        return wordStatisticsJson.find(fieldName) != wordStatisticsJson.end();
    });
    return wordStatisticsValid;
}
}