#include "WordDescriptionParser.h"

#include "boost/algorithm/string.hpp"

namespace
{
void removeMarks(WordDescription&);

void removeDefinitionMarks(Definition&);

void removeExampleMarks(Example&);

void removeSentenceMarks(Sentence&);

bool isDefinition(const std::string&);

bool isExample(const std::string&);

bool isSentence(const std::string&);

const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
}

WordDescription WordDescriptionParser::parse(const std::vector<std::string>& lines) const
{
    WordDescription wordDescription;
    bool previousLineIsExample = false;

    Definition definition;

    for (const auto& line : lines)
    {
        if (previousLineIsExample && !isExample(line))
        {
            wordDescription.definitionsWithExamples.push_back({definition, boost::none});
            previousLineIsExample = false;
        }

        if (isSentence(line))
        {
            wordDescription.sentences.push_back(line);
        }

        if (previousLineIsExample && isExample(line))
        {
            wordDescription.definitionsWithExamples.push_back({definition, line});
            previousLineIsExample = false;
        }

        if (isDefinition(line))
        {
            definition = line;
            previousLineIsExample = true;
        }
    }

    removeMarks(wordDescription);

    return wordDescription;
}

namespace
{
void removeMarks(WordDescription& wordDescription)
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
    boost::erase_all(definition, definitionMark);
    boost::algorithm::trim(definition);
}

void removeExampleMarks(Example& example)
{
    boost::erase_all(example, exampleMark);
    boost::algorithm::trim(example);
}

void removeSentenceMarks(Sentence& sentence)
{
    boost::erase_all(sentence, sentenceMark);
    boost::algorithm::trim(sentence);
}

bool isDefinition(const std::string& line)
{
    return (!line.empty() && line.substr(0, 1) == definitionMark);
}

bool isExample(const std::string& line)
{
    return (line.size() >= 2 && line.substr(0, 2) == exampleMark);
}

bool isSentence(const std::string& line)
{
    return (line.size() >= 2 && line.substr(0, 1) == sentenceMark && line.substr(line.size() - 1, 1) == sentenceMark);
}

}