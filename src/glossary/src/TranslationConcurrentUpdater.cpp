#include "TranslationConcurrentUpdater.h"

#include <thread>

namespace glossary
{

TranslationConcurrentUpdater::TranslationConcurrentUpdater(
    std::shared_ptr<translationService::TranslationService> translationServiceInit,
    std::shared_ptr<translation::TranslationRepository> repository)
    : translationService{std::move(translationServiceInit)}, translationRepository{std::move(repository)}
{
}

void TranslationConcurrentUpdater::update(const dictionary::std::vector<std::string>& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    const auto englishWordsWithoutTranslation = getEnglishWordsWithoutTranslation(englishWords);
    common::ThreadSafeQueue<dictionary::std::string> englishWordsQueue{englishWordsWithoutTranslation};

    for (unsigned threadNumber = 0; threadNumber < amountOfThreads; threadNumber++)
    {
        threadPool.emplace_back(std::thread(&TranslationConcurrentUpdater::loadingTranslationsWorker, this,
                                            std::ref(englishWordsQueue)));
    }

    for (auto& thread : threadPool)
        thread.join();
}

unsigned TranslationConcurrentUpdater::getAmountOfThreads() const
{
    return supportedThreadsCalculator.calculate();
}

dictionary::std::vector<std::string> TranslationConcurrentUpdater::getEnglishWordsWithoutTranslation(
    const dictionary::std::vector<std::string>& englishWords) const
{
    dictionary::std::vector<std::string> englishWordsWithoutTranslation;

    for (const auto& englishWord : englishWords)
    {
        if (not translationRepository->containsTranslation(englishWord))
            englishWordsWithoutTranslation.emplace_back(englishWord);
    }
    return englishWordsWithoutTranslation;
}

void TranslationConcurrentUpdater::loadingTranslationsWorker(
    common::ThreadSafeQueue<dictionary::std::string>& englishWords)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        loadTranslationFromTranslationService(*currentEnglishWord);
    }
}

void TranslationConcurrentUpdater::loadTranslationFromTranslationService(
    const dictionary::std::string& englishWord)
{
    translationService->retrieveTranslation(englishWord, translation::SourceLanguage::English,
                                            translation::TargetLanguage::Polish);
}
}