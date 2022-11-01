#include "DefaultGlossary.h"

#include <iostream>
#include <utility>

#include "../../domain/statistics/src/repositories/StatisticsRepository.h"
#include "collection/StlOperators.h"
#include "collection/StringHelper.h"
#include "fileSystem/GetProjectPath.h"
#include "translation/Language.h"

namespace glossary
{

DefaultGlossary::DefaultGlossary(
    std::shared_ptr<dictionary::DictionaryService> dictionaryServiceInit,
    std::shared_ptr<translationService::TranslationService> translationServiceInit,
    std::shared_ptr<statistics::StatisticsRepository> statisticsRepoInit,
    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionServiceInit,
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdaterInit,
    std::vector<std::shared_ptr<dictionary::DictionaryObserver>> dictionaryObserversInit,
    std::unique_ptr<DictionaryStatisticsCounter> dictionaryStatisticsCounterInit)
    : dictionaryService{std::move(dictionaryServiceInit)},
      translationRetrieverService{std::move(translationServiceInit)},
      statisticsRepository{std::move(statisticsRepoInit)},
      wordDescriptionRetrieverService{std::move(wordDescriptionServiceInit)},
      dictionaryStatisticsCounter{std::move(dictionaryStatisticsCounterInit)},
{
    initialize();
}

void DefaultGlossary::initialize()
{
    dictionaryService->synchronizeDictionaries();

    for (const auto& dictionaryObserver : dictionaryObservers)
    {
        dictionaryService->registerObserver(dictionaryObserver.get());
    }
}

std::optional<std::string> DefaultGlossary::getRandomPolishWord() const
{
    auto dictionaryWord = dictionaryService->getRandomDictionaryWord();
    if (dictionaryWord == std::nullopt)
    {
        std::cerr << "No available dictionary words";
        return std::nullopt;
    }

    if (not dictionaryWord->translation)
    {
        return translationRetrieverService->retrieveTranslation(
            dictionaryWord->englishWord, translation::SourceLanguage::English, translation::TargetLanguage::Polish);
    }

    return dictionaryWord->translation;
}

std::optional<std::string> DefaultGlossary::getRandomPolishWord(const std::string& dictionaryName) const
{
    auto dictionaryWord = dictionaryService->getRandomDictionaryWord(dictionaryName);
    if (dictionaryWord == std::nullopt)
    {
        std::cerr << "No available dictionary words";
        return std::nullopt;
    }

    if (not dictionaryWord->translation)
    {
        return translationRetrieverService->retrieveTranslation(
            dictionaryWord->englishWord, translation::SourceLanguage::English, translation::TargetLanguage::Polish);
    }

    return dictionaryWord->translation;
}

bool DefaultGlossary::verifyPolishWordTranslation(const std::string& polishWord, const std::string& englishWord) const
{
    const auto englishTranslationFromPolishWord = translationRetrieverService->retrieveTranslation(
        polishWord, translation::SourceLanguage::Polish, translation::TargetLanguage::English);
    if (englishTranslationFromPolishWord == std::nullopt)
    {
        return false;
    }

    if (common::collection::compareCaseInsensitive(*englishTranslationFromPolishWord, englishWord))
    {
        statisticsRepository->addCorrectAnswer(englishWord);
        return true;
    }

    statisticsRepository->addIncorrectAnswer(*englishTranslationFromPolishWord);
    return false;
}

std::vector<Dictionary> DefaultGlossary::getDictionaries() const
{
    return dictionaryService->getDictionaries();
}

std::vector<std::string> DefaultGlossary::getDictionariesNames() const
{
    return dictionaryService->getDictionaryNames();
}

std::vector<DictionaryWord> DefaultGlossary::getDictionaryWords(const std::string& dictionaryName) const
{
    if (const auto dictionaryWords = dictionaryService->getDictionaryWords(dictionaryName))
    {
        return *dictionaryWords;
    }
    return {};
}

void DefaultGlossary::addDictionary(const std::string& dictionaryName) const
{
    dictionaryService->addDictionary(dictionaryName);
}

void DefaultGlossary::removeDictionary(const std::string& dictionaryName) const
{
    dictionaryService->removeDictionary(dictionaryName);
}

void DefaultGlossary::addEnglishWordToDictionary(const std::string& englishWord,
                                                 const std::string& dictionaryName) const
{
    dictionaryService->addWordToDictionary({englishWord, std::nullopt}, dictionaryName);
}

void DefaultGlossary::addEnglishWordToDictionary(const std::string& englishWord, const std::string& translation,
                                                 const std::string& dictionaryName) const
{
    dictionaryService->addWordToDictionary({englishWord, translation}, dictionaryName);
}

void DefaultGlossary::removeEnglishWordFromDictionary(const std::string& englishWord,
                                                      const std::string& dictionaryName) const
{
    dictionaryService->removeWordFromDictionary(englishWord, dictionaryName);
}

void DefaultGlossary::addDictionaryFromFile(const std::string& dictionaryName,
                                            const std::string& pathToFileWithDictionaryWords) const
{
    dictionaryService->addDictionaryFromFile(dictionaryName, pathToFileWithDictionaryWords);
}

void DefaultGlossary::updateDictionaryWordTranslationManually(const std::string& dictionaryName,
                                                              const std::string& englishWord,
                                                              const std::string& newTranslation) const
{
    dictionaryService->updateWordTranslationFromDictionary(dictionaryName, englishWord, newTranslation);
}

void DefaultGlossary::updateDictionaryWordTranslationAutomatically(const std::string& dictionaryName,
                                                                   const std::string& englishWord) const
{
    const auto translation = translationService->retrieveTranslation(englishWord, translation::Language::English,
                                                                     translation::Language::Polish);

    if (translation)
    {
        dictionaryService->updateWordTranslationFromDictionary(dictionaryName, englishWord, *translation);
    }
}

void DefaultGlossary::updateDictionaryTranslationsAutomatically(const std::string& dictionaryName) const
{
    const auto dictionaryWords = dictionaryService->getDictionaryWords(dictionaryName);

    if (dictionaryWords)
    {
        for (const auto& dictionaryWord : *dictionaryWords)
        {
            if (dictionaryWord.translation && dictionaryWord.translation->empty())
            {
                updateDictionaryWordTranslation(dictionaryWord.englishWord, dictionaryName);
            }
        }
    }
}

WordDescription DefaultGlossary::getEnglishWordDescription(const std::string& englishWord) const
{
    return wordDescriptionRetrieverService->retrieveWordDescription(englishWord);
}

std::vector<std::string> DefaultGlossary::getSupportedTranslatorLanguages() const
{
    return translationRetrieverService->retrieveSupportedLanguages();
}

std::optional<std::string> DefaultGlossary::translate(const std::string& textToTranslate,
                                                      const std::string& sourceLanguageText,
                                                      const std::string& targetLanguageText) const
{
    translation::Language sourceLanguage;

    if (common::collection::compareCaseInsensitive(sourceLanguageText, "Polish"))
    {
        sourceLanguage = translation::Language::Polish;
    }
    else if (common::collection::compareCaseInsensitive(sourceLanguageText, "English"))
    {
        sourceLanguage = translation::Language::English;
    }
    else
    {
        std::cerr << "Invalid source language\n";
        return std::nullopt;
    }

    translation::Language targetLanguage;
    if (common::collection::compareCaseInsensitive(targetLanguageText, "Polish"))
    {
        targetLanguage = translation::Language::Polish;
    }
    else if (common::collection::compareCaseInsensitive(targetLanguageText, "English"))
    {
        targetLanguage = translation::Language::English;
    }
    else
    {
        std::cerr << "Invalid target language\n";
        return std::nullopt;
    }

    return translationRetrieverService->retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);
}

std::optional<DictionaryStatistics> DefaultGlossary::getDictionaryStatistics(const std::string& dictionaryName) const
{
    const auto dictionary = dictionaryService->getDictionary(dictionaryName);

    if (!dictionary)
    {
        return std::nullopt;
    }

        auto statistics = statisticsRepository->getStatistics();

        return dictionaryStatisticsCounter->countDictionaryStatistics(*dictionary, statistics);
}

DictionariesStatistics DefaultGlossary::getDictionariesStatistics() const
{
    auto dictionaries = dictionaryService->getDictionaries();

    auto statistics = statisticsRepository->getStatistics();

    return dictionaryStatisticsCounter->countDictionariesStatistics(dictionaries, statistics);
}

void DefaultGlossary::resetStatistics() const
{
    statisticsRepository->resetStatistics();
}

}
