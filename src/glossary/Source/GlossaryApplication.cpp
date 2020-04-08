#include "GlossaryApplication.h"

#include <iostream>

#include "DefaultWordViewFormatter.h"
#include "utils/GetProjectPath.h"
#include "utils/StlOperators.h"

namespace glossary
{

GlossaryApplication::GlossaryApplication(
    std::shared_ptr<dictionaryService::DictionaryService> dictionaryServiceInit,
    std::shared_ptr<translationService::TranslationRetrieverService> translationServiceInit,
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepoInit,
    std::shared_ptr<wordDescriptionService::WordDescriptionRetrieverService> wordDescriptionServiceInit,
    std::shared_ptr<DictionarySynchronizer> dictionarySynchronizerInit,
    std::shared_ptr<DictionaryTranslationUpdater> dictionaryTranslationUpdaterInit,
    std::unique_ptr<AnswerValidator> validator, std::unique_ptr<UserPrompt> prompt)
    : dictionaryService{std::move(dictionaryServiceInit)},
      translationRetrieverService{std::move(translationServiceInit)},
      statisticsRepository{std::move(statisticsRepoInit)},
      wordDescriptionRetrieverService{std::move(wordDescriptionServiceInit)},
      dictionarySynchronizer{std::move(dictionarySynchronizerInit)},
      dictionaryTranslationUpdater{std::move(dictionaryTranslationUpdaterInit)},
      answerValidator{std::move(validator)},
      userPrompt{std::move(prompt)}
{
    initialize();
}

void GlossaryApplication::initialize()
{
    wordViewFormatter = std::make_unique<DefaultWordViewFormatter>();
    dictionarySynchronizer->synchronizeDictionaries();
}

void GlossaryApplication::run()
{
    loop();
}

void GlossaryApplication::loop()
{
    auto userWantsToContinue = true;

    while (userWantsToContinue)
    {
        showMenu();
        switch (userPrompt->getIntInput())
        {
        case 1:
            translate();
            break;
        case 2:
            listDictionariesByNames();
            break;
        case 3:
            listDictionaryWordsFromDictionary();
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
            showStatistics();
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

void GlossaryApplication::showMenu() const
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

void GlossaryApplication::translate() const
{
    std::cout << "Insert polish word:\n";
    const auto textToTranslate = userPrompt->getStringInput();
    const auto translation = translationRetrieverService->retrieveTranslation(
        textToTranslate, translator::SourceLanguage::Polish, translator::TargetLanguage::English);
    if (translation)
        std::cout << *translation << "\n";
    else
        std::cout << "no translation\n";
}

void GlossaryApplication::listDictionariesByNames()
{
    std::cout << dictionaryService->getDictionaryNames() << "\n";
}

void GlossaryApplication::listDictionaryWordsFromDictionary()
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << dictionaryService->getDictionaryWords(dictionaryName) << "\n";
}

void GlossaryApplication::addDictionary() const
{
    std::cout << "Insert dictionary name to add:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    dictionaryService->addDictionary(dictionaryName);
}

void GlossaryApplication::addEnglishWordToDictionary() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word:\n";
    const auto englishWord = userPrompt->getStringInput();
    dictionaryService->addWordToDictionary({englishWord, boost::none}, dictionaryName);
}

void GlossaryApplication::removeDictionary() const
{
    std::cout << "Insert dictionary name to remove:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    dictionaryService->removeDictionary(dictionaryName);
}

void GlossaryApplication::removeEnglishWordFromDictionary() const
{
    std::cout << "Insert dictionary name to remove word from:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word:\n";
    const auto englishWord = userPrompt->getStringInput();
    dictionaryService->removeWordFromDictionary(englishWord, dictionaryName);
}

void GlossaryApplication::addDictionaryFromFile() const
{
    std::cout << "Insert dictionary name to add:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert absolute path to words dictionary file(csv format):\n";
    const auto pathToFileWithDictionaryWords = userPrompt->getStringInput();
    dictionaryService->addDictionaryFromFile(dictionaryName, pathToFileWithDictionaryWords);
    dictionarySynchronizer->synchronizeDictionary(dictionaryName);
}

void GlossaryApplication::updateDictionaryWordTranslationManually() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word in which you want to update translation:\n";
    const auto englishWord = userPrompt->getStringInput();
    std::cout << "Insert new translation:\n";
    const auto translation = userPrompt->getStringInput();

    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, translation, dictionaryName);
}

void GlossaryApplication::updateDictionaryWordTranslationAutomatically() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert english word in which you want to update translation:\n";
    const auto englishWord = userPrompt->getStringInput();

    dictionaryTranslationUpdater->updateDictionaryWordTranslation(englishWord, dictionaryName);
}

void GlossaryApplication::updateDictionaryTranslationsAutomatically() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();

    dictionaryTranslationUpdater->updateDictionaryTranslations(dictionaryName);
}

void GlossaryApplication::guessWord() const
{
    const auto& dictionaryWord = dictionaryService->getRandomDictionaryWord();
    if (dictionaryWord == boost::none)
    {
        std::cerr << "No words with translations available";
        return;
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

    const auto wordDescription =
        wordDescriptionRetrieverService->retrieveWordDescription(dictionaryWord->englishWord);
    std::cout << wordViewFormatter->formatWordDescriptionView(wordDescription);
}

void GlossaryApplication::getEnglishWordDescription() const
{
    std::cout << "Insert english word:\n";
    const auto dictionaryWord = userPrompt->getStringInput();
    const auto wordDescription = wordDescriptionRetrieverService->retrieveWordDescription(dictionaryWord);
    std::cout << wordViewFormatter->formatWordDescriptionView(wordDescription) << "\n";
}

void GlossaryApplication::showStatistics() const
{
    std::cout << statisticsRepository->getStatistics() << "\n";
}

void GlossaryApplication::resetStatistics() const
{
    statisticsRepository->resetStatistics();
}

}