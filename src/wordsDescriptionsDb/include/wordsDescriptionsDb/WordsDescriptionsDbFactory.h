#pragma once

#include <memory>

#include "WordsDescriptionsDb.h"
#include "utils/FileAccess.h"

namespace wordsDescriptionsDb
{
class WordsDescriptionsDbFactory
{
public:
    virtual ~WordsDescriptionsDbFactory() = default;

    virtual std::unique_ptr<WordsDescriptionsDb> createWordsDescriptionDb() const = 0;

    static std::unique_ptr<WordsDescriptionsDbFactory>
    createWordsDescriptionsDbFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}