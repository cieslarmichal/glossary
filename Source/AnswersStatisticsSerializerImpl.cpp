#include "AnswersStatisticsSerializerImpl.h"

#include <iostream>

#include "boost/algorithm/cxx11/any_of.hpp"

namespace
{
constexpr auto answersStatisticsField = "answersStatistics";
constexpr auto englishWordField = "englishWord";
constexpr auto correctAnswersField = "correctAnswers";
constexpr auto incorrectAnswersField = "incorrectAnswers";
}

std::string AnswersStatisticsSerializerImpl::serialize(
    const AnswersStatistics& answersStatistics) const
{
    nlohmann::json serialized;
    for (const auto& wordAnswersStatistics : answersStatistics)
    {
        serialized[answersStatisticsField].push_back(
            getJsonFromWordAnswersStatistics(wordAnswersStatistics.second));
    }
    if (serialized.empty())
    {
        return {};
    }
    return serialized.dump();
}

AnswersStatistics
AnswersStatisticsSerializerImpl::deserialize(const std::string& jsonText) const
{
    if (jsonText.empty())
    {
        return {};
    }

    try
    {
        const auto json = nlohmann::json::parse(jsonText);
        return readAnswersStatistics(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse AnswersStatistics:" << e.what();
    }
    return {};
}

nlohmann::json
AnswersStatisticsSerializerImpl::getJsonFromWordAnswersStatistics(
    const AnswersStatisticsPerWord& wordAnswersStatistics) const
{
    nlohmann::json val = nlohmann::json::object();
    val[englishWordField] = wordAnswersStatistics.englishWord;
    val[correctAnswersField] = wordAnswersStatistics.correctAnswers;
    val[incorrectAnswersField] = wordAnswersStatistics.incorrectAnswers;
    return val;
}

AnswersStatistics AnswersStatisticsSerializerImpl::readAnswersStatistics(
    const nlohmann::json& json) const
{
    if (json.find(answersStatisticsField) != json.end())
    {
        return parseAnswersStatistics(json[answersStatisticsField]);
    }
    // info
    std::cerr << "There are no statistics stored\n";
    return {};
}

AnswersStatistics AnswersStatisticsSerializerImpl::parseAnswersStatistics(
    const nlohmann::json& answersStatisticsJson) const
{
    AnswersStatistics answersStatistics;
    for (const auto& answersStatisticsData : answersStatisticsJson)
    {
        if (isWordAnswersStatisticsValid(answersStatisticsData))
        {
            try
            {
                const auto englishWord =
                    answersStatisticsData[englishWordField];
                answersStatistics[englishWord] = AnswersStatisticsPerWord{
                    answersStatisticsData[englishWordField],
                    answersStatisticsData[correctAnswersField],
                    answersStatisticsData[incorrectAnswersField]};
            }
            catch (const std::exception& e)
            {
                std::cerr << "Unable to read wordAnswerStatistics:" << e.what()
                          << "\n";
            }
        }
        else
        {
            std::cerr
                << "wordAnswersStatistics does not contain all required data\n";
        }
    }
    return answersStatistics;
}

bool AnswersStatisticsSerializerImpl::isWordAnswersStatisticsValid(
    const nlohmann::json& wordAnswersStatistics) const
{
    const auto requiredFields = {englishWordField, correctAnswersField,
                                 incorrectAnswersField};
    auto wordInvalid =
        boost::algorithm::any_of(requiredFields, [&](const auto& fieldName) {
            return wordAnswersStatistics.find(fieldName) ==
                   wordAnswersStatistics.end();
        });
    return !wordInvalid;
}
