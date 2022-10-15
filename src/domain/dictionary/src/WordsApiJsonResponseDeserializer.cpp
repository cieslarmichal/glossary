#include "WordsApiJsonResponseDeserializer.h"

#include <iostream>

namespace glossary::dictionary
{

namespace
{
const std::string definitionsField{"definitions"};
const std::string definitionField{"definition"};
const std::string examplesField{"examples"};
const std::string synonymsField{"synonyms"};
}

std::vector<std::string>
WordsApiJsonResponseDeserializer::deserializeDefinitions(const std::string& jsonDefinitions) const
{
    try
    {
        const auto json = nlohmann::json::parse(jsonDefinitions);
        return readDefinitions(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to deserialize definitions:" << e.what();
    }
    return {};
}

std::vector<std::string> WordsApiJsonResponseDeserializer::readDefinitions(const nlohmann::json& json) const
{
    if (json.find(definitionsField) != json.end())
    {
        return parseDefinitions(json[definitionsField]);
    }
    std::cerr << "There are no definitions field in json";
    return {};
}

std::vector<std::string>
WordsApiJsonResponseDeserializer::parseDefinitions(const nlohmann::json& definitionsJson) const
{
    std::vector<std::string> definitionsFromJson{};

    for (const auto& definitionData : definitionsJson)
    {
        if (isJsonDefinitionValid(definitionData))
        {
            definitionsFromJson.push_back(definitionData[definitionField].get<std::string>());
        }
    }
    return definitionsFromJson;
}

bool WordsApiJsonResponseDeserializer::isJsonDefinitionValid(const nlohmann::json& definitionData) const
{
    return definitionData.find(definitionField) != definitionData.end();
}

std::vector<std::string>
WordsApiJsonResponseDeserializer::deserializeExamples(const std::string& jsonExamples) const
{
    try
    {
        const auto json = nlohmann::json::parse(jsonExamples);
        return readExamples(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to deserialize examples:" << e.what();
    }
    return {};
}

std::vector<std::string> WordsApiJsonResponseDeserializer::readExamples(const nlohmann::json& json) const
{
    if (json.find(examplesField) != json.end())
    {
        return json[examplesField].get<std::vector<std::string>>();
    }
    std::cerr << "There are no examples field in json";
    return {};
}

std::vector<std::string>
WordsApiJsonResponseDeserializer::deserializeSynonyms(const std::string& jsonSynonyms) const
{
    try
    {
        const auto json = nlohmann::json::parse(jsonSynonyms);
        return readSynonyms(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to deserialize synonyms:" << e.what();
    }
    return {};
}

std::vector<std::string> WordsApiJsonResponseDeserializer::readSynonyms(const nlohmann::json& json) const
{
    if (json.find(synonymsField) != json.end())
    {
        return json[synonymsField].get<std::vector<std::string>>();
    }
    std::cerr << "There are no synonyms field in json";
    return {};
}

}