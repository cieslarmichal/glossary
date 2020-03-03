#include "WordDescriptionConcurrentGenerator.h"

#include <iostream>
#include <thread>

using namespace wordsDescriptionsDb;

WordDescriptionConcurrentGenerator::WordDescriptionConcurrentGenerator(
    std::unique_ptr<WordDescriptionService> service)
    : wordDescriptionService{std::move(service)}
{
}

WordsDescriptions
WordDescriptionConcurrentGenerator::generateWordsDescriptions(const EnglishWords& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    utils::ThreadSafeQueue<EnglishWord> englishWordsQueue{englishWords};
    utils::ThreadSafeQueue<WordDescription> wordsDescriptions;

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

WordDescription WordDescriptionConcurrentGenerator::generateWordDescription(const EnglishWord& englishWord)
{
    if (const auto wordDescription = wordDescriptionService->getWordDescription(englishWord))
    {
        return *wordDescription;
    }
    return WordDescription{englishWord, {}};
}

void WordDescriptionConcurrentGenerator::generatorWorker(
    utils::ThreadSafeQueue<wordsDescriptionsDb::EnglishWord>& englishWords,
    utils::ThreadSafeQueue<wordsDescriptionsDb::WordDescription>& wordsDescriptions)
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
    std::cerr << amountOfSupportedThreads << " concurrent threads are supported.\n";
    unsigned amountOfThreads = amountOfSupportedThreads !=0 ? amountOfSupportedThreads : defaultAmountOfThreads;
    return amountOfThreads;
}
