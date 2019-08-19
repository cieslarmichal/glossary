#pragma once

struct WordDescription
{
    std::string toString() const
    {
        std::string wordDescription;
        for (auto definitionAndExample : definitionsWithExamples)
        {
            wordDescription += definitionAndExample.first + "\n";
            wordDescription += definitionAndExample.second + "\n";
        }

        for (auto sentence : sentences)
        {
            wordDescription += sentence + "\n";
        }

        wordDescription += "\n";
    }

    std::vector<std::pair<std::string, std::string>> definitionsWithExamples;
    std::vector<std::string> sentences;
};