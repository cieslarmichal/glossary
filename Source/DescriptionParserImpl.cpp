#include "DescriptionParserImpl.h"

#include "boost/algorithm/string.hpp"

using namespace wordsDb::wordsDescriptionsDb;

namespace
{
void removeMarks(Description&);
void removeDefinitionMarks(Definition&);
void removeExampleMarks(Example&);
void removeSentenceMarks(Sentence&);
bool isDefinition(const std::string&);
bool isExample(const std::string&);
bool isSentence(const std::string&);
void trimEmptySpaces(std::string&);

const std::string definitionPrefix{": "};
const std::string examplePrefix{"// "};
const std::string sentencePrefix{"; "};
}

boost::optional<Description>
DescriptionParserImpl::parse(const std::vector<std::string>& lines) const
{
    Description wordDescription;
    bool previousLineIsDefinition = false;

    Definition definition;

    for (const auto& line : lines)
    {
        if (previousLineIsDefinition && !isExample(line))
        {
            wordDescription.definitionsWithExamples.push_back(
                {definition, boost::none});
            previousLineIsDefinition = false;
        }

        if (isSentence(line))
        {
            wordDescription.sentences.push_back(line);
        }

        if (previousLineIsDefinition && isExample(line))
        {
            wordDescription.definitionsWithExamples.push_back(
                {definition, line});
            previousLineIsDefinition = false;
        }

        if (isDefinition(line))
        {
            definition = line;
            previousLineIsDefinition = true;
            if (line == lines.back())
            {
                wordDescription.definitionsWithExamples.push_back(
                    {definition, boost::none});
            }
        }
    }

    if (wordDescription.empty())
    {
        return boost::none;
    }

    removeMarks(wordDescription);
    return wordDescription;
}

namespace
{
void removeMarks(Description& wordDescription)
{
    for (auto& definitionAndExample : wordDescription.definitionsWithExamples)
    {
        removeDefinitionMarks(definitionAndExample.definition);
        if (definitionAndExample.example)
        {
            removeExampleMarks(*definitionAndExample.example);
        }
    }

    for (auto& sentence : wordDescription.sentences)
    {
        removeSentenceMarks(sentence);
    }
}

void removeDefinitionMarks(Definition& definition)
{
    definition.erase(0, definitionPrefix.size());
    trimEmptySpaces(definition);
}

void removeExampleMarks(Example& example)
{
    example.erase(0, examplePrefix.size());
    trimEmptySpaces(example);
}

void removeSentenceMarks(Sentence& sentence)
{
    sentence.erase(0, sentencePrefix.size());
    trimEmptySpaces(sentence);
}

bool isDefinition(const std::string& line)
{
    return line.rfind(definitionPrefix, 0) != std::string::npos;
}

bool isExample(const std::string& line)
{
    return line.rfind(examplePrefix, 0) != std::string::npos;
}

bool isSentence(const std::string& line)
{
    return line.rfind(sentencePrefix, 0) != std::string::npos;
}

void trimEmptySpaces(std::string& line)
{
    boost::algorithm::trim(line);
}

}
