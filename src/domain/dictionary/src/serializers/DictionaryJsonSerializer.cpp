#include "DictionaryJsonSerializer.h"

#include "fmt/core.h"

#include "exceptions/DictionaryJsonMissingRequiredFieldsError.h"
#include "exceptions/InvalidJsonError.h"

namespace glossary::dictionary
{
namespace
{
nlohmann::json parseJsonText(const std::string& jsonText);
void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName);

constexpr auto dictionaryNameField = "dictionaryName";
constexpr auto dictionaryWordsField = "dictionaryWords";
constexpr auto englishWordField = "englishWord";
constexpr auto translationField = "translation";
}

std::string DictionaryJsonSerializer::serialize(const std::vector<Dictionary>& dictionaries) const
{
    nlohmann::json serializedDictionaries = nlohmann::json::array();

    for (const auto& dictionary : dictionaries)
    {
        nlohmann::json dictionaryJson;

        dictionaryJson[dictionaryNameField] = dictionary.name;

        nlohmann::json dictionaryWordsJson = nlohmann::json::array();

        for (const auto& word : dictionary.words)
        {
            nlohmann::json dictionaryWordJson;

            dictionaryWordJson[englishWordField] = word.englishWord;

            if (word.translation)
            {
                dictionaryWordJson[translationField] = *word.translation;
            }

            dictionaryWordsJson.emplace_back(dictionaryWordJson);
        }

        dictionaryJson[dictionaryWordsField] = dictionaryWordsJson;

        serializedDictionaries.push_back(dictionaryJson);
    }

    return serializedDictionaries.empty() ? "{}" : serializedDictionaries.dump();
}

std::vector<Dictionary> DictionaryJsonSerializer::deserialize(const std::string& jsonText) const
{
    const auto json = parseJsonText(jsonText);

    if (json.empty())
    {
        return {};
    }

    std::vector<Dictionary> dictionaries;

    for (const auto& dictionaryJsonData : json)
    {
        validateFieldExistence(dictionaryJsonData, dictionaryNameField);

        validateFieldExistence(dictionaryJsonData, dictionaryWordsField);

        const auto dictionaryName = dictionaryJsonData[dictionaryNameField].get<std::string>();

        std::vector<DictionaryWord> dictionaryWords;

        for (const auto& dictionaryWordData : dictionaryJsonData[dictionaryWordsField])
        {
            validateFieldExistence(dictionaryWordData, englishWordField);

            const auto englishWord = dictionaryWordData[englishWordField].get<std::string>();

            const auto translation = dictionaryWordData.find(translationField) == dictionaryWordData.end() ?
                                         std::optional<std::string>(std::nullopt) :
                                         dictionaryWordData[translationField].get<std::string>();

            dictionaryWords.push_back({englishWord, translation});
        }

        dictionaries.push_back({dictionaryName, dictionaryWords});
    }

    return dictionaries;
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
        throw exceptions::DictionaryJsonMissingRequiredFieldsError{fmt::format("Missing {} field.", fieldName)};
    }
}
}

}
