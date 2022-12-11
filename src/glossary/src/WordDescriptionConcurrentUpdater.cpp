#include "WordDescriptionConcurrentUpdater.h"

#include <iostream>
#include <thread>

namespace glossary
{

WordDescriptionConcurrentUpdater::WordDescriptionConcurrentUpdater(
    std::shared_ptr<dictionary::GetWordDescriptionQuery> getWordDescriptionQueryInit)
    : getWordDescriptionQuery{std::move(getWordDescriptionQueryInit)}
{
}

void WordDescriptionConcurrentUpdater::update(const std::vector<std::string>& englishWords)
{
    const auto amountOfThreads = supportedThreadsCalculator.calculate();

    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    common::collection::ThreadSafeQueue<std::string> englishWordsQueue{englishWords};

    for (unsigned threadNumber = 0; threadNumber < amountOfThreads; threadNumber++)
    {
        threadPool.emplace_back(
            std::thread(&WordDescriptionConcurrentUpdater::getWordDescriptions, this, std::ref(englishWordsQueue)));
    }

    for (auto& thread : threadPool)
    {
        thread.join();
    }
}

void WordDescriptionConcurrentUpdater::getWordDescriptions(
    common::collection::ThreadSafeQueue<std::string>& englishWords)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        getWordDescriptionQuery->getWordDescription(*currentEnglishWord);
    }
}

}
