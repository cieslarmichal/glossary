#pragma once

#include <memory>

#include "collection/ThreadSafeQueue.h"
#include "concurrency/SupportedThreadsCalculator.h"
#include "translation/queries/GetTranslationQuery.h"

namespace glossary
{
class TranslationConcurrentUpdater
{
public:
    explicit TranslationConcurrentUpdater(std::shared_ptr<translation::GetTranslationQuery>);

    void update(const std::vector<std::string>& englishWords);

private:
    void getTranslations(common::collection::ThreadSafeQueue<std::string>&);

    std::shared_ptr<translation::GetTranslationQuery> getTranslationQuery;
    common::concurrency::SupportedThreadsCalculator supportedThreadsCalculator;
};
}
