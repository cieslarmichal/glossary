#include "DescriptionSerializer.h"

namespace wordsDescriptionsDb
{
namespace
{
constexpr auto definitionsWithExamplesField = "definitionsWithExamples";
constexpr auto definitionField = "definition";
constexpr auto exampleField = "example";
constexpr auto sentencesField = "sentences";
}

nlohmann::json DescriptionSerializer::serialize(const Description& description) const
{
    return getJsonFromDescription(description);
}

Description DescriptionSerializer::deserialize(const nlohmann::json& json) const
{
    return getDescriptionFromJson(json);
}

nlohmann::json DescriptionSerializer::getJsonFromDescription(const Description& description) const
{
    nlohmann::json val = nlohmann::json::object();

    for (const auto& definitionWithExample : description.definitionsWithExamples)
    {
        val[definitionsWithExamplesField].push_back(getJsonFromDefinitionAndExample(definitionWithExample));
    }

    for (const auto& sentence : description.sentences)
    {
        val[sentencesField].push_back(sentence);
    }
    return val;
}

nlohmann::json DescriptionSerializer::getJsonFromDefinitionAndExample(
    const DefinitionWithExample& definitionWithExample) const
{
    nlohmann::json json;
    json[definitionField] = definitionWithExample.definition;
    if (definitionWithExample.example)
    {
        json[exampleField] = *definitionWithExample.example;
    }
    return json;
}

Description DescriptionSerializer::getDescriptionFromJson(const nlohmann::json& jsonText) const
{
    DefinitionsWithExamples definitionsWithExamples{};
    Sentences sentences{};

    if (jsonText.find(definitionsWithExamplesField) != jsonText.end())
    {
        for (const auto& definitionWithExample : jsonText[definitionsWithExamplesField])
        {
            definitionsWithExamples.push_back(getDefinitionAndExampleFromJson(definitionWithExample));
        }
    }

    if (jsonText.find(sentencesField) != jsonText.end())
    {
        sentences = jsonText[sentencesField].get<std::vector<std::string>>();
    }

    return Description{definitionsWithExamples, sentences};
}

DefinitionWithExample DescriptionSerializer::getDefinitionAndExampleFromJson(const nlohmann::json& json) const
{
    DefinitionWithExample definitionWithExample{};
    if (json.find(definitionField) != json.end())
    {
        definitionWithExample.definition = json[definitionField].get<std::string>();
    }
    if (json.find(exampleField) != json.end())
    {
        definitionWithExample.example = json[exampleField].get<std::string>();
    }
    return definitionWithExample;
}

}
