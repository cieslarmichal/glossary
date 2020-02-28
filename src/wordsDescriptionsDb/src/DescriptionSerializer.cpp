#include "DescriptionSerializer.h"

#include "nlohmann/json.hpp"

namespace wordsDescriptionsDb
{

namespace
{
nlohmann::json getJsonFromDescription(const Description&);

Description readDescription(const nlohmann::json&);

constexpr auto definitionsWithExamplesField = "definitionsWithExamples";
constexpr auto sentencesField = "sentences";
}

nlohmann::json
DescriptionSerializer::serialize(const Description& description) const
{
    return getJsonFromDescription(description);
}

Description DescriptionSerializer::deserialize(const nlohmann::json& json) const
{
    if (json.empty())
    {
        return {};
    }

    return readDescription(json);
}

namespace
{

nlohmann::json getJsonFromDescription(const Description& description)
{
    nlohmann::json val = nlohmann::json::object();

    for (const auto& defExample : description.definitionsWithExamples)
    {
        val[definitionsWithExamplesField].push_back(defExample.toString());
    }

    for (const auto& sentence : description.sentences)
    {
        val[sentencesField].push_back(sentence);
    }

    return val;
}

Description readDescription(const nlohmann::json& jsonText)
{
    DefinitionsWithExamples definitionsWithExamples;
    Sentences sentences;

    if (jsonText.find(definitionsWithExamplesField) != jsonText.end())
    {
        for (const auto& definitionWithExample :
             jsonText[definitionsWithExamplesField])
        {
            definitionsWithExamples.push_back(
                toDefinitionWithExample(definitionWithExample));
        }
    }

    if (jsonText.find(sentencesField) != jsonText.end())
    {
        for (const auto& sentence : jsonText[sentencesField])
        {
            sentences.push_back(sentence);
        }
    }

    return Description{definitionsWithExamples, sentences};
}

}
}