#include "TranslationConcurrentLoader.h"

#include <thread>

namespace glossary
{

TranslationConcurrentLoader::TranslationConcurrentLoader(
    std::shared_ptr<translationService::TranslationRetrieverService> translationServiceInit,
    std::shared_ptr<translationRepository::TranslationRepository> repository)
    : translationService{std::move(translationServiceInit)}, translationRepository{std::move(repository)}
{
}

void TranslationConcurrentLoader::loadMissingTranslations(
    const wordDescriptionRepository::EnglishWords& englishWords)
{
    const auto amountOfThreads = getAmountOfThreads();
    std::vector<std::thread> threadPool;
    threadPool.reserve(amountOfThreads);

    const auto englishWordsWithoutTranslation = getEnglishWordsWithoutTranslation(englishWords);
    utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord> englishWordsQueue{
        englishWordsWithoutTranslation};

    for (unsigned threadNumber = 0; threadNumber < amountOfThreads; threadNumber++)
    {
        threadPool.emplace_back(std::thread(&TranslationConcurrentLoader::loadingTranslationsWorker, this,
                                            std::ref(englishWordsQueue)));
    }

    for (auto& thread : threadPool)
        thread.join();
}

unsigned TranslationConcurrentLoader::getAmountOfThreads() const
{
    return supportedThreadsCalculator.calculate();
}

wordDescriptionRepository::EnglishWords TranslationConcurrentLoader::getEnglishWordsWithoutTranslation(
    const wordDescriptionRepository::EnglishWords& englishWords) const
{
    wordDescriptionRepository::EnglishWords englishWordsWithoutTranslation;

    for (const auto& englishWord : englishWords)
    {
        if (not translationRepository->containsTranslation(englishWord))
            englishWordsWithoutTranslation.emplace_back(englishWord);
    }
    return englishWordsWithoutTranslation;
}

void TranslationConcurrentLoader::loadingTranslationsWorker(
    utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>& englishWords)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        loadTranslationFromTranslationService(*currentEnglishWord);
    }
}

void TranslationConcurrentLoader::loadTranslationFromTranslationService(
    const wordDescriptionRepository::EnglishWord& englishWord)
{
    translationService->retrieveTranslation(englishWord, translator::SourceLanguage::English,
                                            translator::TargetLanguage::Polish);
}
}