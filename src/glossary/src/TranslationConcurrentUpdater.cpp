#include "TranslationConcurrentUpdater.h"

#include <thread>

#include "translation/Language.h"

namespace glossary
{

TranslationConcurrentUpdater::TranslationConcurrentUpdater(
    std::shared_ptr<translation::GetTranslationQuery> getTranslationQueryInit)
    : getTranslationQuery{std::move(getTranslationQueryInit)}
{
}

void TranslationConcurrentUpdater::update(const std::vector<std::string>& englishWords)
{
    const auto amountOfThreads = supportedThreadsCalculator.calculate();

    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    common::collection::ThreadSafeQueue<std::string> englishWordsQueue{englishWords};

    for (unsigned threadNumber = 0; threadNumber < amountOfThreads; threadNumber++)
    {
        threadPool.emplace_back(
            std::thread(&TranslationConcurrentUpdater::getTranslations, this, std::ref(englishWordsQueue)));
    }

    for (auto& thread : threadPool)
    {
        thread.join();
    }
}

void TranslationConcurrentUpdater::getTranslations(common::collection::ThreadSafeQueue<std::string>& englishWords)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        getTranslationQuery->getTranslation(
            {*currentEnglishWord, translation::Language::English, translation::Language::Polish});
    }
}

}
