#include "TranslationConcurrentUpdater.h"

#include <thread>

namespace glossary
{

TranslationConcurrentUpdater::TranslationConcurrentUpdater(
    std::shared_ptr<translationService::TranslationService> translationServiceInit,
    std::shared_ptr<translationRepository::TranslationRepository> repository)
    : translationService{std::move(translationServiceInit)}, translationRepository{std::move(repository)}
{
}

void TranslationConcurrentUpdater::update(const dictionaryService::EnglishWords& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    const auto englishWordsWithoutTranslation = getEnglishWordsWithoutTranslation(englishWords);
    utils::ThreadSafeQueue<dictionaryService::EnglishWord> englishWordsQueue{englishWordsWithoutTranslation};

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
    utils::ThreadSafeQueue<dictionaryService::EnglishWord>& englishWords)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        loadTranslationFromTranslationService(*currentEnglishWord);
    }
}

void TranslationConcurrentUpdater::loadTranslationFromTranslationService(
    const dictionaryService::EnglishWord& englishWord)
{
    translationService->retrieveTranslation(englishWord, translator::SourceLanguage::English,
                                            translator::TargetLanguage::Polish);
}
}