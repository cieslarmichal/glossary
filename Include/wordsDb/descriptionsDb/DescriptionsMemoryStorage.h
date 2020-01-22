#pragma once

#include "DescriptionsStorage.h"
#include "boost/optional.hpp"

namespace wordsDb::descriptionsDb
{

class DescriptionsMemoryStorage : public DescriptionsStorage
{
public:
    void addWord(const WordDescription&) override;
    boost::optional<WordDescription> getWord(const EnglishWord&) const override;
    Words getWords() const override;
    bool contains(const EnglishWord&) const override;
    Words::size_type size() const override;
    bool empty() const override;
    Words::const_iterator begin() const override;
    Words::const_iterator end() const override;

private:
    Words words;
};
}
