#pragma once

#include "Storage.h"
#include "boost/optional.hpp"

class StorageImpl : public Storage
{
public:
    explicit StorageImpl(const std::vector<Word> &);
    StorageImpl() = default;

    void addWord(const Word &) override;
    boost::optional<Word> getWord(const EnglishWord &) const override;
    Words getWords() const override;
    Words::size_type size() const override;
    bool empty() const override;
    Words::const_iterator begin() const override;
    Words::const_iterator end() const override;

private:
    bool wordExists(const Word &) const;

    std::vector<Word> words;
};
