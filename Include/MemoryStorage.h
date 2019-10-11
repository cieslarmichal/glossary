#pragma once

#include "Storage.h"
#include "boost/optional.hpp"

class MemoryStorage : public Storage
{
public:
    void addWord(const Word &) override;
    boost::optional<Word> getWord(const EnglishWord &) const override;
    Words getWords() const override;
    Words::size_type size() const override;
    bool empty() const override;
    Words::const_iterator begin() const override;
    Words::const_iterator end() const override;

private:
    bool contains(const Word &) const;

    std::vector<Word> words;
};
