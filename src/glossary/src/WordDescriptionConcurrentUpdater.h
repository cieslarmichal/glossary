#pragma once

#include <memory>

#include "collection/ThreadSafeQueue.h"
#include "concurrency/SupportedThreadsCalculator.h"
#include "dictionary/queries/GetWordDescriptionQuery.h"
#include "dictionary/WordDescription.h"

namespace glossary
{
class WordDescriptionConcurrentUpdater
{
public:
    explicit WordDescriptionConcurrentUpdater(std::shared_ptr<dictionary::GetWordDescriptionQuery>);

    void update(const std::vector<std::string>& englishWords);

private:
    void getWordDescriptions(common::collection::ThreadSafeQueue<std::string>& englishWords);

    std::shared_ptr<dictionary::GetWordDescriptionQuery> getWordDescriptionQuery;
    common::concurrency::SupportedThreadsCalculator supportedThreadsCalculator;
};
}
