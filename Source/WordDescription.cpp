#include "WordDescription.h"
#include <iostream>

namespace
{
bool isDefinition(const std::string &);

bool isExample(const std::string &);

bool isSentence(const std::string &);

const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
}


WordDescription::WordDescription(const std::vector<std::string> &lines)
{
    bool example_flag = false;

    std::string definition;

    for (auto line : lines)
    {
        if (example_flag && !isExample(line))
        {
            definitionsWithExamples.emplace_back(std::make_pair(definition, ""));
            example_flag = false;
        }

        if (isSentence(line))
        {
            sentences.push_back(line);
        }

        if (example_flag && isExample(line))
        {
            definitionsWithExamples.emplace_back(std::make_pair(definition, line));
            example_flag = false;
        }

        if (isDefinition(line))
        {
            definition = line;
            example_flag = true;
        }
    }
}


std::string WordDescription::toString() const
{
    std::string wordDescription;
    for (const auto & definitionAndExample : definitionsWithExamples)
    {
        wordDescription += definitionAndExample.first + "\n";
        wordDescription += definitionAndExample.second + "\n";
    }

    for (const auto & sentence : sentences)
    {
        wordDescription += sentence + "\n";
    }

    wordDescription += "\n";

    return wordDescription;
}


namespace
{
bool isDefinition(const std::string &line)
{
    return (!line.empty() && line.substr(0, 1) == definitionMark);
}

bool isExample(const std::string &line)
{
    return (line.size() >= 2 && line.substr(0, 2) == exampleMark);
}

bool isSentence(const std::string &line)
{
    return (line.size() >= 2 && line.substr(0, 1) == sentenceMark && line.substr(line.size() - 1, 1) == sentenceMark);
}

}

