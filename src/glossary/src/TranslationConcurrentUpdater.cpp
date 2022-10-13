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

void TranslationConcurrentUpdater::update(const dictionaryService::EnglishWords& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    const auto englishWordsWithoutTranslation = getEnglishWordsWithoutTranslation(englishWords);
    common::ThreadSafeQueue<dictionaryService::std::string> englishWordsQueue{englishWordsWithoutTranslation};

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

dictionaryService::EnglishWords TranslationConcurrentUpdater::getEnglishWordsWithoutTranslation(
    const dictionaryService::EnglishWords& englishWords) const
{
    dictionaryService::EnglishWords englishWordsWithoutTranslation;

    for (const auto& englishWord : englishWords)
    {
        if (not translationRepository->containsTranslation(englishWord))
            englishWordsWithoutTranslation.emplace_back(englishWord);
    }
    return englishWordsWithoutTranslation;
}

void TranslationConcurrentUpdater::loadingTranslationsWorker(
    common::ThreadSafeQueue<dictionaryService::std::string>& englishWords)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        loadTranslationFromTranslationService(*currentEnglishWord);
    }
}

void TranslationConcurrentUpdater::loadTranslationFromTranslationService(
    const dictionaryService::std::string& englishWord)
{
    translationService->retrieveTranslation(englishWord, translation::SourceLanguage::English,
                                            translation::TargetLanguage::Polish);
}
}