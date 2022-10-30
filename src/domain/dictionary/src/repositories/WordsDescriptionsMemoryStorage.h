#pragma once

#include "WordsDescriptionsStorage.h"

namespace glossary::dictionary
{
class WordsDescriptionsMemoryStorage : public WordsDescriptionsStorage
{
public:
    void addWordDescription(const WordDescription&) override;
    std::optional<WordDescription> getWordDescription(const std::string&) const override;
    std::vector<WordDescription> getWordsDescriptions() const override;
    bool contains(const std::string&) const override;
    std::vector<WordDescription>::size_type size() const override;
    bool empty() const override;

private:
    std::vector<WordDescription>::const_iterator getWordsDescriptionsIter(const std::string&) const;

    std::vector<WordDescription> wordsDescriptions;
};
}
