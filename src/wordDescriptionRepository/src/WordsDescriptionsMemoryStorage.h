#pragma once

#include "WordsDescriptionsStorage.h"

namespace wordDescriptionRepository
{
class WordsDescriptionsMemoryStorage : public WordsDescriptionsStorage
{
public:
    void addWordDescription(const WordDescription&) override;
    boost::optional<WordDescription> getWordDescription(const EnglishWord&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const EnglishWord&) const override;
    WordsDescriptions::size_type size() const override;
    bool empty() const override;

private:
    WordsDescriptions::const_iterator getWordsDescriptionsIter(const EnglishWord&) const;

    WordsDescriptions wordsDescriptions;
};
}
