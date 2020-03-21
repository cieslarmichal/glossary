#pragma once

#include "WordsDescriptionsDbFactory.h"

namespace wordsDescriptionsDb
{
class DefaultWordsDescriptionsDbFactory : public WordsDescriptionsDbFactory
{
public:
    explicit DefaultWordsDescriptionsDbFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<WordsDescriptionsDb> createWordsDescriptionDb() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}