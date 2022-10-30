#include "WordsStatisticsJsonSerializer.h"

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/WordsStatisticsJsonMissingRequiredFieldsError.h"

namespace glossary::statistics
{
namespace
{
nlohmann::json parseJsonText(const std::string& jsonText);
void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName);

constexpr auto englishWordField = "englishWord";
constexpr auto correctAnswersField = "correctAnswers";
constexpr auto incorrectAnswersField = "incorrectAnswers";
}

std::string WordsStatisticsJsonSerializer::serialize(const std::vector<WordStatistics>& wordsStatistics) const
{
    nlohmann::json serializedWordsStatistics = nlohmann::json::array();

    for (const auto& wordStatistics : wordsStatistics)
    {
        nlohmann::json wordStatisticsJson;

        wordStatisticsJson[englishWordField] = wordStatistics.englishWord;
        wordStatisticsJson[correctAnswersField] = wordStatistics.correctAnswers;
        wordStatisticsJson[incorrectAnswersField] = wordStatistics.incorrectAnswers;

        serializedWordsStatistics.push_back(wordStatisticsJson);
    }

    return serializedWordsStatistics.empty() ? "[]" : serializedWordsStatistics.dump();
}

std::vector<WordStatistics> WordsStatisticsJsonSerializer::deserialize(const std::string& jsonText) const
{
    const auto json = parseJsonText(jsonText);

    if (json.empty())
    {
        return {};
    }

    std::vector<WordStatistics> wordsStatistics;

    for (const auto& wordStatisticsJsonData : json)
    {
        validateFieldExistence(wordStatisticsJsonData, englishWordField);
        validateFieldExistence(wordStatisticsJsonData, correctAnswersField);
        validateFieldExistence(wordStatisticsJsonData, incorrectAnswersField);

        wordsStatistics.emplace_back(WordStatistics{wordStatisticsJsonData[englishWordField].get<std::string>(),
                                                    wordStatisticsJsonData[correctAnswersField].get<int>(),
                                                    wordStatisticsJsonData[incorrectAnswersField].get<int>()});
    }

    return wordsStatistics;
}

namespace
{
nlohmann::json parseJsonText(const std::string& jsonText)
{
    try
    {
        return nlohmann::json::parse(jsonText);
    }
    catch (const std::exception& e)
    {
        throw exceptions::InvalidJsonError{e.what()};
    }
}

void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName)
{
    if (data.find(fieldName) == data.end())
    {
        throw exceptions::WordsStatisticsJsonMissingRequiredFieldsError{fmt::format("Missing {} field.", fieldName)};
    }
}
}
}
