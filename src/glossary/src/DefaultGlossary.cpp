#include "DefaultGlossary.h"

#include <iostream>
#include <utility>

#include "DefaultWordViewFormatter.h"
#include "utils/GetProjectPath.h"
#include "utils/StlOperators.h"

namespace glossary
{

DefaultGlossary::DefaultGlossary(
    std::shared_ptr<dictionaryService::DictionaryService> dictionaryServiceInit,
    std::shared_ptr<translationService::TranslationRetrieverService> translationServiceInit,
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepoInit,
    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService> wordDescriptionServiceInit,
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdaterInit,
    std::vector<std::shared_ptr<dictionaryService::DictionaryObserver>> dictionaryObserversInit,
    std::unique_ptr<ConnectionChecker> connectionCheckerInit, std::unique_ptr<AnswerValidator> validator,
    std::unique_ptr<UserPrompt> prompt)
    : dictionaryService{std::move(dictionaryServiceInit)},
      translationRetrieverService{std::move(translationServiceInit)},
      statisticsRepository{std::move(statisticsRepoInit)},
      wordDescriptionRetrieverService{std::move(wordDescriptionServiceInit)},
      dictionaryTranslationUpdater{std::move(dictionaryTranslationUpdaterInit)},
      dictionaryObservers(std::move(dictionaryObserversInit)),
      connectionChecker{std::move(connectionCheckerInit)},
      answerValidator{std::move(validator)},
      userPrompt{std::move(prompt)},
      wordViewFormatter{std::make_unique<DefaultWordViewFormatter>()}
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

bool DefaultGlossary::connectionIsAvailable() const
{
    return connectionChecker->connectionAvailable() &&
           translationRetrieverService->connectionToTranslateApiAvailable();
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

boost::optional<std::string> DefaultGlossary::getRandomPolishWord(const std::string& dictionaryName) const
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
    const auto englishTranslationFromPolishWord = translationRetrieverService->retrieveTranslation(polishWord,
                                                                                               translator::SourceLanguage::Polish,
                                                                                               translator::TargetLanguage::English);
    if(englishTranslationFromPolishWord == boost::none)
    {
        return false;
    }

    if (answerValidator->validateAnswer(*englishTranslationFromPolishWord, englishWord))
    {
        statisticsRepository->addCorrectAnswer(englishWord);
        return true;
    }

    statisticsRepository->addIncorrectAnswer(englishWord);
    return false;
}

boost::optional<std::string> DefaultGlossary::translate() const
{
    std::cout << "Supported languages: " << translationRetrieverService->retrieveSupportedLanguages() << "\n";

    std::cout << "Insert word to translate:\n";
    const auto textToTranslate = userPrompt->getStringInput();

    std::cout << "Insert source language:\n";
    const auto sourceLanguageText = userPrompt->getStringInput();

    translator::SourceLanguage sourceLanguage;
    // TODO: connect with supported languages
    if (answerValidator->validateAnswer(sourceLanguageText, "Polish"))
        sourceLanguage = translator::Language::Polish;
    else if (answerValidator->validateAnswer(sourceLanguageText, "English"))
        sourceLanguage = translator::Language::English;
    else
    {
        std::cerr << "Invalid source language\n";
        return boost::none;
    }

    std::cout << "Insert target language:\n";
    const auto targetLanguageText = userPrompt->getStringInput();

    translator::TargetLanguage targetLanguage;
    if (answerValidator->validateAnswer(targetLanguageText, "Polish"))
        targetLanguage = translator::Language::Polish;
    else if (answerValidator->validateAnswer(targetLanguageText, "English"))
        targetLanguage = translator::Language::English;
    else
    {
        std::cerr << "Invalid target language\n";
        return boost::none;
    }

    return translationRetrieverService->retrieveTranslation(textToTranslate, sourceLanguage, targetLanguage);
}

std::vector<std::string> DefaultGlossary::listDictionariesByNames()
{
    return dictionaryService->getDictionaryNames();
}

std::vector<std::string> DefaultGlossary::listDictionaryWordsFromDictionary()
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::vector<std::string> dictionaryWordsAsString;
    if (const auto dictionaryWords = dictionaryService->getDictionaryWords(dictionaryName))
    {
        for (const auto& dictionaryWord : *dictionaryWords)
            dictionaryWordsAsString.push_back(toString(dictionaryWord));
    }
    return dictionaryWordsAsString;
}

void DefaultGlossary::addDictionary() const
{
    std::cout << "Insert dictionary name to add:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    dictionaryService->addDictionary(dictionaryName);
}

void DefaultGlossary::addEnglishWordToDictionary() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word:\n";
    const auto englishWord = userPrompt->getStringInput();
    dictionaryService->addWordToDictionary({englishWord, boost::none}, dictionaryName);
}

void DefaultGlossary::removeDictionary() const
{
    std::cout << "Insert dictionary name to remove:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    dictionaryService->removeDictionary(dictionaryName);
}

void DefaultGlossary::removeEnglishWordFromDictionary() const
{
    std::cout << "Insert dictionary name to remove word from:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word:\n";
    const auto englishWord = userPrompt->getStringInput();
    dictionaryService->removeWordFromDictionary(englishWord, dictionaryName);
}

void DefaultGlossary::addDictionaryFromFile() const
{
    std::cout << "Insert dictionary name to add:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert absolute path to words dictionary file(csv format):\n";
    const auto pathToFileWithDictionaryWords = userPrompt->getStringInput();
    dictionaryService->addDictionaryFromFile(dictionaryName, pathToFileWithDictionaryWords);
}

void DefaultGlossary::updateDictionaryWordTranslationManually() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word in which you want to update translation:\n";
    const auto englishWord = userPrompt->getStringInput();
    std::cout << "Insert new translation:\n";
    const auto translation = userPrompt->getStringInput();

    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, translation, dictionaryName);
}

void DefaultGlossary::updateDictionaryWordTranslationAutomatically() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word in which you want to update translation:\n";
    const auto englishWord = userPrompt->getStringInput();

    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, dictionaryName);
}

void DefaultGlossary::updateDictionaryTranslationsAutomatically() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();

    dictionaryTranslationUpdater->updateDictionaryTranslations(dictionaryName);
}

std::string DefaultGlossary::getEnglishWordDescription() const
{
    std::cout << "Insert english word:\n";
    const auto englishWord = userPrompt->getStringInput();
    const auto wordDescription = wordDescriptionRetrieverService->retrieveWordDescription(englishWord);
    std::cout << wordViewFormatter->formatWordDescriptionView(wordDescription) << "\n";
    return toString(wordDescription);
}

std::vector<std::string> DefaultGlossary::showStatistics() const
{
    std::vector<std::string> statisticsAsString;
    for (const auto& wordStatistics : statisticsRepository->getStatistics())
        statisticsAsString.push_back(toString(wordStatistics));
    return statisticsAsString;
}

void DefaultGlossary::resetStatistics() const
{
    statisticsRepository->resetStatistics();
}

}