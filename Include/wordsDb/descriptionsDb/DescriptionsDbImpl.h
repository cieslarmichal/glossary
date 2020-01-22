#pragma once

#include <memory>

#include "DescriptionsDb.h"
#include "wordsDb/descriptionsDb/DescriptionsStorage.h"

namespace wordsDb::descriptionsDb
{
class DescriptionsDbImpl : public DescriptionsDb
{
public:
    explicit DescriptionsDbImpl(std::unique_ptr<DescriptionsStorage>);

    void addWord(const WordDescription&) const override;
    boost::optional<WordDescription> getWord(const EnglishWord&) const override;
    bool contains(const EnglishWord&) const override;

private:
    std::unique_ptr<DescriptionsStorage> storage;
};
}
