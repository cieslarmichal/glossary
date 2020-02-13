#pragma once

#include <memory>

#include "WordsDescriptionsDb.h"
#include "WordsDescriptionsStorage.h"

namespace wordsDescriptionsDb
{

class WordsDescriptionsDbImpl : public WordsDescriptionsDb
{
public:
    explicit WordsDescriptionsDbImpl(std::unique_ptr<WordsDescriptionsStorage>);

    void addWordDescription(const WordDescription&) const override;
    boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const EnglishWord&) const override;

private:
    std::unique_ptr<WordsDescriptionsStorage> storage;
};
}
