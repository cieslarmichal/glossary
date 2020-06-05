#include "DefaultGlossary.h"

#include <iostream>
#include <utility>

#include "utils/GetProjectPath.h"
#include "utils/StlOperators.h"

namespace glossary
{

DefaultGlossary::DefaultGlossary(
    std::shared_ptr<dictionaryService::DictionaryService> dictionaryServiceInit,
    std::shared_ptr<translationService::TranslationService> translationServiceInit,
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepoInit,
    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionServiceInit,
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdaterInit,
    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>> dictionaryObserversInit,
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

boost::optional<std::string> DefaultGlossary::getRandomPolishWord() const
{
    auto dictionaryWord = dictionaryService->getRandomDictionaryWord();
    if (dictionaryWord == boost::none)
    {
        std::cerr << "No available dictionary words";
        return boost::none;
    }

    if (not dictionaryWord->translation)
    {
        return translationRetrieverService->retrieveTranslation(dictionaryWord->englishWord,
                                                                translator::SourceLanguage::English,
                                                                translator::TargetLanguage::Polish);
    }

    return dictionaryWord->translation;
}

boost::optional<std::string> DefaultGlossary::getRandomPolishWord(const DictionaryName& dictionaryName) const
{
    auto dictionaryWord = dictionaryService->getRandomDictionaryWord(dictionaryName);
    if (dictionaryWord == boost::none)
    {
        std::cerr << "No available dictionary words";
        return boost::none;
    }

    if (not dictionaryWord->translation)
    {
        return translationRetrieverService->retrieveTranslation(dictionaryWord->englishWord,
                                                                translator::SourceLanguage::English,
                                                                translator::TargetLanguage::Polish);
    }

    return dictionaryWord->translation;
}

bool DefaultGlossary::verifyPolishWordTranslation(const std::string& polishWord,
                                                  const std::string& englishWord) const
{
    const auto englishTranslationFromPolishWord = translationRetrieverService->retrieveTranslation(
        polishWord, translator::SourceLanguage::Polish, translator::TargetLanguage::English);
    if (englishTranslationFromPolishWord == boost::none)
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

Dictionaries DefaultGlossary::getDictionaries() const
{
    return dictionaryService->getDictionaries();
}

DictionaryNames DefaultGlossary::getDictionariesNames() const
{
    return dictionaryService->getDictionaryNames();
}

DictionaryWords DefaultGlossary::getDictionaryWords(const DictionaryName& dictionaryName) const
{
    if (const auto dictionaryWords = dictionaryService->getDictionaryWords(dictionaryName))
    {
        return *dictionaryWords;
    }
    return {};
}

void DefaultGlossary::addDictionary(const DictionaryName& dictionaryName) const
{
    dictionaryService->addDictionary(dictionaryName);
}

void DefaultGlossary::removeDictionary(const DictionaryName& dictionaryName) const
{
    dictionaryService->removeDictionary(dictionaryName);
}

void DefaultGlossary::addEnglishWordToDictionary(const EnglishWord& englishWord,
                                                 const DictionaryName& dictionaryName) const
{
    dictionaryService->addWordToDictionary({englishWord, boost::none}, dictionaryName);
}

void DefaultGlossary::addEnglishWordToDictionary(const EnglishWord& englishWord,
                                                 const std::string& translation,
                                                 const DictionaryName& dictionaryName) const
{
    dictionaryService->addWordToDictionary({englishWord, translation}, dictionaryName);
}

void DefaultGlossary::removeEnglishWordFromDictionary(const EnglishWord& englishWord,
                                                      const DictionaryName& dictionaryName) const
{
    dictionaryService->removeWordFromDictionary(englishWord, dictionaryName);
}

void DefaultGlossary::addDictionaryFromFile(const DictionaryName& dictionaryName,
                                            const std::string& pathToFileWithDictionaryWords) const
{
    dictionaryService->addDictionaryFromFile(dictionaryName, pathToFileWithDictionaryWords);
}

void DefaultGlossary::updateDictionaryWordTranslationManually(const DictionaryName& dictionaryName,
                                                              const EnglishWord& englishWord,
                                                              const std::string& newTranslation) const
{
    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, newTranslation,
                                                                  dictionaryName);
}

void DefaultGlossary::updateDictionaryWordTranslationAutomatically(const DictionaryName& dictionaryName,
                                                                   const EnglishWord& englishWord) const
{
    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, dictionaryName);
}

void DefaultGlossary::updateDictionaryTranslationsAutomatically(const DictionaryName& dictionaryName) const
{
    dictionaryTranslationUpdater->updateDictionaryTranslations(dictionaryName);
}

WordDescription DefaultGlossary::getEnglishWordDescription(const EnglishWord& englishWord) const
{
    return wordDescriptionRetrieverService->retrieveWordDescription(englishWord);
}

std::vector<std::string> DefaultGlossary::getSupportedTranslatorLanguages() const
{
    return translationRetrieverService->retrieveSupportedLanguages();
}

boost::optional<std::string> DefaultGlossary::translate(const std::string& textToTranslate,
                                                        const std::string& sourceLanguageText,
                                                        const std::string& targetLanguageText) const
{
    translator::SourceLanguage sourceLanguage;
    if (answerValidator->validateAnswer(sourceLanguageText, "Polish"))
    {
        sourceLanguage = translator::Language::Polish;
    }
    else if (answerValidator->validateAnswer(sourceLanguageText, "English"))
    {
        sourceLanguage = translator::Language::English;
    }
    else
    {
        std::cerr << "Invalid source language\n";
        return boost::none;
    }

    translator::TargetLanguage targetLanguage;
    if (answerValidator->validateAnswer(targetLanguageText, "Polish"))
    {
        targetLanguage = translator::Language::Polish;
    }
    else if (answerValidator->validateAnswer(targetLanguageText, "English"))
    {
        targetLanguage = translator::Language::English;
    }
    else
    {
        std::cerr << "Invalid target language\n";
        return boost::none;
    }

    return translationRetrieverService->retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);
}

boost::optional<DictionaryStatistics>
DefaultGlossary::getDictionaryStatistics(const DictionaryName& dictionaryName) const
{
    if (auto dictionary = dictionaryService->getDictionary(dictionaryName))
    {
        auto statistics = statisticsRepository->getStatistics();
        return dictionaryStatisticsCounter->countDictionaryStatistics(*dictionary, statistics);
    }
    return boost::none;
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
