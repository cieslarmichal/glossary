#include "WordDescriptionConcurrentGenerator.h"

#include <thread>

WordDescriptionConcurrentGenerator::WordDescriptionConcurrentGenerator(
    std::shared_ptr<WordDescriptionRetrieverService> service)
    : wordDescriptionRetrieverService{std::move(service)}
{
}

wordDescriptionRepository::WordsDescriptions WordDescriptionConcurrentGenerator::generateWordsDescriptions(
    const wordDescriptionRepository::EnglishWords& englishWords)
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

wordDescriptionRepository::WordDescription WordDescriptionConcurrentGenerator::generateWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord)
{
    if (const auto wordDescription = wordDescriptionRetrieverService->retrieveWordDescription(englishWord))
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
    return amountOfSupportedThreadsCalculator.calculate();
}
