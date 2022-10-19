#include "DefaultGlossary.h"

#include <iostream>
#include <utility>

#include "GetProjectPath.h"
#include "collection/StlOperators.h"

namespace glossary
{

DefaultGlossary::DefaultGlossary(
    std::shared_ptr<dictionary::DictionaryService> dictionaryServiceInit,
    std::shared_ptr<translationService::TranslationService> translationServiceInit,
    std::shared_ptr<statistics::StatisticsRepository> statisticsRepoInit,
    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionServiceInit,
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdaterInit,
    std::vector<std::shared_ptr<dictionary::DictionaryObserver>> dictionaryObserversInit,
    std::unique_ptr<DictionaryStatisticsCounter> dictionaryStatisticsCounterInit,
    std::unique_ptr<ConnectionChecker> connectionCheckerInit, std::unique_ptr<AnswerValidator> validator)
    : dictionaryService{std::move(dictionaryServiceInit)},
      translationRetrieverService{std::move(translationServiceInit)},
      statisticsRepository{std::move(statisticsRepoInit)},
      wordDescriptionRetrieverService{std::move(wordDescriptionServiceInit)},
      dictionaryTranslationUpdater{std::move(dictionaryTranslationUpdaterInit)},
      dictionaryObservers(std::move(dictionaryObserversInit)),
      dictionaryStatisticsCounter{std::move(dictionaryStatisticsCounterInit)},
      externalServicesConnectionChecker{std::move(connectionCheckerInit)},
      answerValidator{std::move(validator)}
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

ExternalServicesStatus DefaultGlossary::checkConnectionToExternalServices() const
{
    return externalServicesConnectionChecker->checkExternalServicesAvailabilityStatus();
}

void DefaultGlossary::updateTranslateApiKeyLocation(const std::string& apiKeyLocation) const
{
    translationRetrieverService->updateApiKeyLocation(apiKeyLocation);
}

void DefaultGlossary::updateWordsApiKeyLocation(const std::string& apiKeyLocation) const
{
    wordDescriptionRetrieverService->updateApiKeyLocation(apiKeyLocation);
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
        return translationRetrieverService->retrieveTranslation(dictionaryWord->englishWord,
                                                                translation::SourceLanguage::English,
                                                                translation::TargetLanguage::Polish);
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
        return translationRetrieverService->retrieveTranslation(dictionaryWord->englishWord,
                                                                translation::SourceLanguage::English,
                                                                translation::TargetLanguage::Polish);
    }

    return dictionaryWord->translation;
}

bool DefaultGlossary::verifyPolishWordTranslation(const std::string& polishWord,
                                                  const std::string& englishWord) const
{
    const auto englishTranslationFromPolishWord = translationRetrieverService->retrieveTranslation(
        polishWord, translation::SourceLanguage::Polish, translation::TargetLanguage::English);
    if (englishTranslationFromPolishWord == std::nullopt)
    {
        return false;
    }

    if (answerValidator->validateAnswer(*englishTranslationFromPolishWord, englishWord))
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

void DefaultGlossary::addEnglishWordToDictionary(const std::string& englishWord,
                                                 const std::string& translation,
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
    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, newTranslation,
                                                                  dictionaryName);
}

void DefaultGlossary::updateDictionaryWordTranslationAutomatically(const std::string& dictionaryName,
                                                                   const std::string& englishWord) const
{
    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, dictionaryName);
}

void DefaultGlossary::updateDictionaryTranslationsAutomatically(const std::string& dictionaryName) const
{
    dictionaryTranslationUpdater->updateDictionaryTranslations(dictionaryName);
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
    translation::SourceLanguage sourceLanguage;
    if (answerValidator->validateAnswer(sourceLanguageText, "Polish"))
    {
        sourceLanguage = translation::Language::Polish;
    }
    else if (answerValidator->validateAnswer(sourceLanguageText, "English"))
    {
        sourceLanguage = translation::Language::English;
    }
    else
    {
        std::cerr << "Invalid source language\n";
        return std::nullopt;
    }

    translation::TargetLanguage targetLanguage;
    if (answerValidator->validateAnswer(targetLanguageText, "Polish"))
    {
        targetLanguage = translation::Language::Polish;
    }
    else if (answerValidator->validateAnswer(targetLanguageText, "English"))
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

std::optional<DictionaryStatistics>
DefaultGlossary::getDictionaryStatistics(const std::string& dictionaryName) const
{
    if (auto dictionary = dictionaryService->getDictionary(dictionaryName))
    {
        auto statistics = statisticsRepository->getStatistics();
        return dictionaryStatisticsCounter->countDictionaryStatistics(*dictionary, statistics);
    }
    return std::nullopt;
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
