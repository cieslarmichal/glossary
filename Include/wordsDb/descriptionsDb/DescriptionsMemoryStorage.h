#pragma once

#include "DescriptionsStorage.h"
#include "boost/optional.hpp"

namespace wordsDb::descriptionsDb
{

class DescriptionsMemoryStorage : public DescriptionsStorage
{
public:
    void addWordDescription(const WordDescription&) override;
    boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const EnglishWord&) const override;
    WordsDescriptions::size_type size() const override;
    bool empty() const override;
    WordsDescriptions::const_iterator begin() const override;
    WordsDescriptions::const_iterator end() const override;

private:
    WordsDescriptions::const_iterator getWordIter(const EnglishWord&) const;

    WordsDescriptions words;
};
}
