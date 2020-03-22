#include "WordDescriptionConcurrentGenerator.h"

#include <iostream>
#include <thread>

WordDescriptionConcurrentGenerator::WordDescriptionConcurrentGenerator(
    std::unique_ptr<WordDescriptionService> service)
    : wordDescriptionService{std::move(service)}
{
}

wordDescriptionRepository::WordsDescriptions
WordDescriptionConcurrentGenerator::generateWordsDescriptions(const wordDescriptionRepository::EnglishWords& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord> englishWordsQueue{englishWords};
    utils::ThreadSafeQueue<wordDescriptionRepository::WordDescription> wordsDescriptions;

    for (unsigned i = 0; i < amountOfThreads; i++)
    {
        threadPool.emplace_back(std::thread(&WordDescriptionConcurrentGenerator::generatorWorker, this,
                                            std::ref(englishWordsQueue), std::ref(wordsDescriptions)));
    }

    for (auto& thread : threadPool)
    {
        thread.join();
    }

    return wordsDescriptions.popAll();
}

wordDescriptionRepository::WordDescription WordDescriptionConcurrentGenerator::generateWordDescription(const wordDescriptionRepository::EnglishWord& englishWord)
{
    if (const auto wordDescription = wordDescriptionService->getWordDescription(englishWord))
    {
        return *wordDescription;
    }
    return wordDescriptionRepository::WordDescription{englishWord, {}};
}

void WordDescriptionConcurrentGenerator::generatorWorker(
    utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>& englishWords,
    utils::ThreadSafeQueue<wordDescriptionRepository::WordDescription>& wordsDescriptions)
{
    while (not englishWords.empty())
    {
        if (const auto currentEnglishWord = englishWords.pop())
        {
            const auto generatedWordDescription = generateWordDescription(*currentEnglishWord);
            wordsDescriptions.push(generatedWordDescription);
        }
    }
}

unsigned WordDescriptionConcurrentGenerator::getAmountOfThreads() const
{
    constexpr auto defaultAmountOfThreads = 4;
    unsigned amountOfSupportedThreads = std::thread::hardware_concurrency();
    unsigned amountOfThreads =
        amountOfSupportedThreads != 0 ? amountOfSupportedThreads : defaultAmountOfThreads;
    return amountOfThreads;
}
