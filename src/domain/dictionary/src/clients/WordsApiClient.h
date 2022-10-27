#pragma once

#include "WordDescription.h"

namespace glossary::dictionary
{
class WordsApiClient
{
public:
    virtual ~WordsApiClient() = default;

    virtual std::vector<std::string> getWordDefinitions(const std::string& englishWord) const = 0;
    virtual std::vector<std::string> getWordExamples(const std::string& englishWord) const = 0;
    virtual std::vector<std::string> getWordSynonyms(const std::string& englishWord) const = 0;
};
}
