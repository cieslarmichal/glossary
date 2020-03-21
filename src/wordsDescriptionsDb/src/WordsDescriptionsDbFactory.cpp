#include "WordsDescriptionsDbFactory.h"

#include "DefaultWordsDescriptionsDbFactory.h"
#include "utils/FileAccess.h"

namespace wordsDescriptionsDb
{
std::unique_ptr<WordsDescriptionsDbFactory> WordsDescriptionsDbFactory::createWordsDescriptionsDbFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultWordsDescriptionsDbFactory>(fileAccess);
}
}
