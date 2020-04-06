#include "WordDescriptionConcurrentLoader.h"

#include <thread>

namespace glossary
{

WordDescriptionConcurrentLoader::WordDescriptionConcurrentLoader(
    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloaderInit,
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepositoryInit)
    : wordDescriptionDownloader{std::move(wordDescriptionDownloaderInit)},
      wordDescriptionRepository{std::move(wordDescriptionRepositoryInit)}
{
}

void WordDescriptionConcurrentLoader::loadWordsDescriptions(
    const wordDescriptionRepository::EnglishWords& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord> englishWordsQueue{englishWords};

    for (unsigned i = 0; i < amountOfThreads; i++)
    {
        threadPool.emplace_back(std::thread(&WordDescriptionConcurrentLoader::loadingWordDescriptionWorker,
                                            this, std::ref(englishWordsQueue)));
    }

    for (auto& thread : threadPool)
        thread.join();
}

void WordDescriptionConcurrentLoader::loadingWordDescriptionWorker(
    utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>& englishWords)
{
    while (not englishWords.empty())
    {
        if (const auto currentEnglishWord = englishWords.pop())
            loadWordDescription(*currentEnglishWord);
    }
}

void WordDescriptionConcurrentLoader::loadWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord)
{
    if (not wordDescriptionRepository->contains(englishWord))
    {
        if (const auto wordDescription = wordDescriptionDownloader->downloadWordDescription(englishWord))
            wordDescriptionRepository->addWordDescription(*wordDescription);
    }
}

unsigned WordDescriptionConcurrentLoader::getAmountOfThreads() const
{
    return supportedThreadsCalculator.calculate();
}

}