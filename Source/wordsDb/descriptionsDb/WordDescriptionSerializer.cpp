#include "wordsDb/descriptionsDb/WordDescriptionSerializer.h"

#include <iostream>

#include "nlohmann/json.hpp"

namespace wordsDb::descriptionsDb
{

namespace
{
nlohmann::json getJsonFromWord(const Description&);

Description readWordDescription(const nlohmann::json&);

constexpr auto definitionsWithExamplesField = "definitionsWithExamples";
constexpr auto sentencesField = "sentences";
}

nlohmann::json
WordDescriptionSerializer::serialize(const Description& wordDescription) const
{
    return getJsonFromWord(wordDescription);
}

Description
WordDescriptionSerializer::deserialize(const nlohmann::json& json) const
{
    if (json.empty())
    {
        return {};
    }
    try
    {
        return readWordDescription(json);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unable to parse wordDescription\n";
    }
    return {};
}

namespace
{

nlohmann::json getJsonFromWord(const Description& wordDescription)
{
    nlohmann::json val = nlohmann::json::object();

    for (const auto& defExample : wordDescription.definitionsWithExamples)
    {
        val[definitionsWithExamplesField].push_back(defExample.toString());
    }

    for (const auto& sentence : wordDescription.sentences)
    {
        val[sentencesField].push_back(sentence);
    }

    return val;
}

Description readWordDescription(const nlohmann::json& jsonText)
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
