#pragma once

#include <memory>

#include "DescriptionsDb.h"
#include "DescriptionsStorage.h"

namespace wordsDb::descriptionsDb
{

class DescriptionsDbImpl : public DescriptionsDb
{
public:
    explicit DescriptionsDbImpl(std::unique_ptr<DescriptionsStorage>);

    void addWordDescription(const WordDescription&) const override;
    boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const EnglishWord&) const override;

private:
    std::unique_ptr<DescriptionsStorage> storage;
};
}
