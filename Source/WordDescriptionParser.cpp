#include "WordDescriptionParser.h"

namespace
{
bool isDefinition(const std::string &);

bool isExample(const std::string &);

bool isSentence(const std::string &);

const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
}


WordDescription WordDescriptionParser::parse(const std::vector<std::string> & lines) const
{
    WordDescription wordDescription;
    bool isPreviousLineExample = false;

    std::string definition;

    for (const auto & line : lines)
    {
        if (isPreviousLineExample && !isExample(line))
        {
            wordDescription.definitionsWithExamples.push_back({definition, ""});
            isPreviousLineExample = false;
        }

        if (isSentence(line))
        {
            wordDescription.sentences.push_back(line);
        }

        if (isPreviousLineExample && isExample(line))
        {
            wordDescription.definitionsWithExamples.push_back({definition, line});
            isPreviousLineExample = false;
        }

        if (isDefinition(line))
        {
            definition = line;
            isPreviousLineExample = true;
        }
    }
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