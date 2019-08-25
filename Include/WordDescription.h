#pragma once

#include <string>
#include <vector>
#include <ostream>

struct WordDescription
{
    WordDescription() = default;
    explicit WordDescription(const std::string &);
    //TODO: bad constructor
    explicit WordDescription(const std::string &, const std::vector<std::string> &);

    bool operator==(const WordDescription&);

    std::string toString() const;

    std::string name;
    std::vector<std::pair<std::string, std::string>> definitionsWithExamples;
    std::vector<std::string> sentences;
};

std::ostream & operator<<(std::ostream &,const WordDescription&);
