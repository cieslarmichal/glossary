#pragma once

#include <string>
#include <vector>

namespace glossary::dictionary
{
class DictionaryNamesRetriever
{
public:
    virtual ~DictionaryNamesRetriever() = default;

    virtual std::vector<std::string> retrieveDictionaryNames() const = 0;
    virtual std::vector<std::string>
    retrieveDictionaryNamesContainingEnglishWord(const std::string& englishWord) const = 0;
    virtual std::vector<std::string> retrieveDictionaryNamesContainingEnglishWordTranslation(
        const std::string& englishWordTranslation) const = 0;
};
}