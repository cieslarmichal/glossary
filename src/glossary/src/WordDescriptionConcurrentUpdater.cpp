#include "WordDescriptionConcurrentUpdater.h"

#include <iostream>
#include <thread>

namespace glossary
{

WordDescriptionConcurrentUpdater::WordDescriptionConcurrentUpdater(
    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionServiceInit,
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepositoryInit)
    : wordDescriptionService{std::move(wordDescriptionServiceInit)},
      wordDescriptionRepository{std::move(wordDescriptionRepositoryInit)}
{
}

void WordDescriptionConcurrentUpdater::update(const dictionary::std::vector<std::string>& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    const auto englishWordsWithoutWordDescriptions = getEnglishWordsWithoutWordDescription(englishWords);
    common::ThreadSafeQueue<wordDescriptionRepository::std::string> englishWordsQueue{
        englishWordsWithoutWordDescriptions};
    common::ThreadSafeQueue<wordDescriptionRepository::WordDescription> wordsDescriptions;

    for (unsigned threadNumber = 0; threadNumber < amountOfThreads; threadNumber++)
    {
        threadPool.emplace_back(std::thread(&WordDescriptionConcurrentUpdater::loadingWordDescriptionWorker,
                                            this, std::ref(englishWordsQueue), std::ref(wordsDescriptions)));
    }

    for (auto& thread : threadPool)
    {
        thread.join();
    }

    loadWordsDescriptionsIntoRepository(wordsDescriptions.popAll());
}

unsigned WordDescriptionConcurrentUpdater::getAmountOfThreads() const
{
    return supportedThreadsCalculator.calculate();
}

wordDescriptionRepository::std::vector<std::string>
WordDescriptionConcurrentUpdater::getEnglishWordsWithoutWordDescription(
    const wordDescriptionRepository::std::vector<std::string>& englishWords) const
{
    wordDescriptionRepository::std::vector<std::string> englishWordsWithoutWordDescription;

    for (const auto& englishWord : englishWords)
    {
        if (not wordDescriptionRepository->contains(englishWord))
        {
            englishWordsWithoutWordDescription.emplace_back(englishWord);
        }
    }
    return englishWordsWithoutWordDescription;
}

void WordDescriptionConcurrentUpdater::loadingWordDescriptionWorker(
    common::ThreadSafeQueue<wordDescriptionRepository::std::string>& englishWords,
    common::ThreadSafeQueue<wordDescriptionRepository::WordDescription>& wordsDescriptions)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        if (const auto downloadedWordDescription = downloadWordDescription(*currentEnglishWord))
        {
            wordsDescriptions.push(*downloadedWordDescription);
        }
    }
}

std::optional<wordDescriptionRepository::WordDescription>
WordDescriptionConcurrentUpdater::downloadWordDescription(
    const wordDescriptionRepository::std::string& englishWord)
{
    return wordDescriptionService->downloadWordDescription(englishWord);
}

void WordDescriptionConcurrentUpdater::loadWordsDescriptionsIntoRepository(
    const wordDescriptionRepository::WordsDescriptions& wordsDescriptions)
{
    for (const auto& wordDescription : wordsDescriptions)
    {
        wordDescriptionRepository->addWordDescription(wordDescription);
    }
}

}