#pragma once

#include <string>
#include <vector>

struct WordDescription
{
    WordDescription() = default;
    explicit WordDescription(const std::vector<std::string> &);

    std::string toString() const;

    std::vector<std::pair<std::string, std::string>> definitionsWithExamples;
    std::vector<std::string> sentences;
};