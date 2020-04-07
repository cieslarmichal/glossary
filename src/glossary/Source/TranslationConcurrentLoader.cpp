#include "TranslationConcurrentLoader.h"

#include <thread>

namespace glossary
{

TranslationConcurrentLoader::TranslationConcurrentLoader(
    std::shared_ptr<translator::Translator> translatorInit,
    std::shared_ptr<translationRepository::TranslationRepository> repository)
    : translator{std::move(translatorInit)}, translationRepository{std::move(repository)}
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
    utils::ThreadSafeQueue<translationRepository::Translation> translations;

    for (unsigned threadNumber = 0; threadNumber < amountOfThreads; threadNumber++)
    {
        threadPool.emplace_back(std::thread(&TranslationConcurrentLoader::loadingTranslationsWorker, this,
                                            std::ref(englishWordsQueue), std::ref(translations)));
    }

    for (auto& thread : threadPool)
        thread.join();

    loadTranslationsIntoRepository(translations.popAll());
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
    utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>& englishWords,
    utils::ThreadSafeQueue<translationRepository::Translation>& translations)
{
    while (const auto currentEnglishWord = englishWords.pop())
    {
        if (const auto translation = getTranslationFromTranslator(*currentEnglishWord))
            translations.push(*translation);
    }
}

boost::optional<translationRepository::Translation> TranslationConcurrentLoader::getTranslationFromTranslator(
    const wordDescriptionRepository::EnglishWord& englishWord)
{
    if (const auto translation = translator->translate(englishWord, translator::SourceLanguage::English,
                                                       translator::TargetLanguage::Polish))
    {
        return translationRepository::Translation{englishWord, *translation};
    }
    return boost::none;
}

void TranslationConcurrentLoader::loadTranslationsIntoRepository(
    const translationRepository::Translations& translations)
{
    for (const auto& translation : translations)
        translationRepository->addTranslation(translation);
}

}