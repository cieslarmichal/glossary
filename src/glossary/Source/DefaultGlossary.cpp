#include "DefaultGlossary.h"

#include <iostream>

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
    std::shared_ptr<DictionarySynchronizer> dictionarySynchronizerInit,
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdaterInit,
    std::unique_ptr<ConnectionChecker> connectionCheckerInit, std::unique_ptr<AnswerValidator> validator,
    std::unique_ptr<UserPrompt> prompt)
    : dictionaryService{std::move(dictionaryServiceInit)},
      translationRetrieverService{std::move(translationServiceInit)},
      statisticsRepository{std::move(statisticsRepoInit)},
      wordDescriptionRetrieverService{std::move(wordDescriptionServiceInit)},
      dictionarySynchronizer{std::move(dictionarySynchronizerInit)},
      dictionaryTranslationUpdater{std::move(dictionaryTranslationUpdaterInit)},
      connectionChecker{std::move(connectionCheckerInit)},
      answerValidator{std::move(validator)},
      userPrompt{std::move(prompt)},
      wordViewFormatter{std::make_unique<DefaultWordViewFormatter>()}
{
    initialize();
}

void DefaultGlossary::initialize()
{
    dictionarySynchronizer->synchronizeDictionaries();
}

void DefaultGlossary::run()
{
    if (not connectionIsAvailable())
        return;

    loop();
}

bool DefaultGlossary::connectionIsAvailable() const
{
    return connectionChecker->connectionAvailable();
}

void DefaultGlossary::loop()
{
    auto userWantsToContinue = true;

    while (userWantsToContinue)
    {
        showMenu();
        switch (userPrompt->getNumberInput())
        {
        case 1:
            std::cout << translate();
            break;
        case 2:
            std::cout << listDictionariesByNames();
            break;
        case 3:
            std::cout << listDictionaryWordsFromDictionary();
            break;
        case 4:
            addDictionary();
            break;
        case 5:
            addEnglishWordToDictionary();
            break;
        case 6:
            removeDictionary();
            break;
        case 7:
            removeEnglishWordFromDictionary();
            break;
        case 8:
            addDictionaryFromFile();
            break;
        case 9:
            updateDictionaryWordTranslationManually();
            break;
        case 10:
            updateDictionaryWordTranslationAutomatically();
            break;
        case 11:
            updateDictionaryTranslationsAutomatically();
            break;
        case 12:
            guessWord();
            break;
        case 13:
            getEnglishWordDescription();
            break;
        case 14:
            std::cout << showStatistics();
            break;
        case 15:
            resetStatistics();
            break;
        default:
            std::cout << "\nLeaving glossary...\n";
            userWantsToContinue = false;
        }
    }
}

void DefaultGlossary::showMenu() const
{
    std::cout << "\nChoose glossary mode:\n";
    std::cout << "1.Translate\n";
    std::cout << "2.List dictionaries names\n";
    std::cout << "3.List dictionary words from dictionary\n";
    std::cout << "4.Add dictionary\n";
    std::cout << "5.Add english word to dictionary\n";
    std::cout << "6.Remove dictionary\n";
    std::cout << "7.Remove english word from dictionary\n";
    std::cout << "8.Add dictionary from file\n";
    std::cout << "9.Update word translation in dictionary manually\n";
    std::cout << "10.Update word translation in dictionary automatically\n";
    std::cout << "11.Update words translations in dictionary automatically\n";
    std::cout << "12.Guess english word\n";
    std::cout << "13.Get word description\n";
    std::cout << "14.Show statistics\n";
    std::cout << "15.Reset statistics\n";
    std::cout << "Insert other number to exit\n";
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
    dictionarySynchronizer->synchronizeDictionary(dictionaryName);
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

void DefaultGlossary::guessWord() const
{
    auto dictionaryWord = dictionaryService->getRandomDictionaryWord();
    if (dictionaryWord == boost::none)
    {
        std::cerr << "No words with translations available";
        return;
    }
    if (not dictionaryWord->translation)
    {
        if (auto translation = translationRetrieverService->retrieveTranslation(
                dictionaryWord->englishWord, translator::SourceLanguage::English,
                translator::TargetLanguage::Polish))
        {
            dictionaryWord->translation = *translation;
        }
        else
        {
            return;
        }
    }

    std::cout << wordViewFormatter->formatSingleWordView(*dictionaryWord->translation);
    std::cout << "Insert english translation:\n";

    if (answerValidator->validateAnswer(userPrompt->getStringInput(), dictionaryWord->englishWord))
    {
        std::cout << "Correct answer!\n";
        statisticsRepository->addCorrectAnswer(dictionaryWord->englishWord);
    }
    else
    {
        std::cout << "Incorrect answer :(\n";
        statisticsRepository->addIncorrectAnswer(dictionaryWord->englishWord);
    }
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