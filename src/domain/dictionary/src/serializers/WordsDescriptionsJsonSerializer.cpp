#include "WordsDescriptionsJsonSerializer.h"

#include "fmt/core.h"

#include "exceptions/InvalidJsonError.h"
#include "exceptions/WordDescriptionJsonMissingRequiredFieldsError.h"

namespace glossary::dictionary
{
namespace
{
nlohmann::json parseJsonText(const std::string& jsonText);
void validateFieldExistence(const nlohmann::json& data, const std::string& fieldName);

constexpr auto englishWordField = "englishWord";
constexpr auto definitionsField = "definitions";
constexpr auto examplesField = "examples";
constexpr auto synonymsField = "synonyms";
}

std::string WordsDescriptionsJsonSerializer::serialize(const std::vector<WordDescription>& wordsDescriptions) const
{
    nlohmann::json serializedWordsDescriptions = nlohmann::json::array();

    for (const auto& wordDescription : wordsDescriptions)
    {
        nlohmann::json wordDescriptionJson;

        wordDescriptionJson[englishWordField] = wordDescription.englishWord;
        wordDescriptionJson[definitionsField] = wordDescription.definitions;
        wordDescriptionJson[examplesField] = wordDescription.examples;
        wordDescriptionJson[synonymsField] = wordDescription.synonyms;

        serializedWordsDescriptions.push_back(wordDescriptionJson);
    }

    return serializedWordsDescriptions.empty() ? "[]" : serializedWordsDescriptions.dump();
}

std::vector<WordDescription> WordsDescriptionsJsonSerializer::deserialize(const std::string& jsonText) const
{
    const auto json = parseJsonText(jsonText);

    if (json.empty())
    {
        return {};
    }

    std::vector<WordDescription> wordsDescriptions;

    for (const auto& wordDescriptionData : json)
    {
        validateFieldExistence(wordDescriptionData, englishWordField);
        validateFieldExistence(wordDescriptionData, definitionsField);
        validateFieldExistence(wordDescriptionData, examplesField);
        validateFieldExistence(wordDescriptionData, synonymsField);

        WordDescription wordDescription{wordDescriptionData[englishWordField].get<std::string>(),
                                        wordDescriptionData[definitionsField].get<std::vector<std::string>>(),
                                        wordDescriptionData[examplesField].get<std::vector<std::string>>(),
                                        wordDescriptionData[synonymsField].get<std::vector<std::string>>()};
        wordsDescriptions.emplace_back(wordDescription);
    }

    return wordsDescriptions;
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
        throw exceptions::WordDescriptionJsonMissingRequiredFieldsError{fmt::format("Missing {} field.", fieldName)};
    }
}
}
}
