#pragma once

#include "WordsDescriptionsStorage.h"

namespace glossary::dictionary
{
class WordsDescriptionsMemoryStorage : public WordsDescriptionsStorage
{
public:
    void addWordDescription(const WordDescription&) override;
    std::optional<WordDescription> getWordDescription(const std::string&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const std::string&) const override;
    WordsDescriptions::size_type size() const override;
    bool empty() const override;

private:
    WordsDescriptions::const_iterator getWordsDescriptionsIter(const std::string&) const;

    WordsDescriptions wordsDescriptions;
};
}
