#pragma once

#include "DictionaryWord.h"

namespace glossary::dictionary
{
class DictionaryWordsRetriever
{
public:
    virtual ~DictionaryWordsRetriever() = default;

    virtual std::optional<std::vector<DictionaryWord>>
    retrieveDictionaryWords(const std::string&) const = 0;
    virtual std::optional<std::vector<std::string>> retrieveEnglishWords(const std::string&) const = 0;
    virtual std::vector<std::string> retrieveEnglishWords() const = 0;
};
}