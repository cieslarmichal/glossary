#include "GlossaryApplication.h"

#include <iostream>

#include "DefaultAnswerValidator.h"
#include "DefaultTranslationRetrieverService.h"
#include "DefaultWordDescriptionRetrieverService.h"
#include "DefaultWordViewFormatter.h"
#include "UserStandardInputPrompt.h"
#include "WordDescriptionConcurrentGenerator.h"
#include "dictionaryService/DictionaryServiceFactory.h"
#include "statisticsRepository/StatisticsRepositoryFactory.h"
#include "translationRepository/TranslationRepositoryFactory.h"
#include "translator/TranslatorFactory.h"
#include "utils/GetProjectPath.h"
#include "utils/StlOperators.h"
#include "webConnection/HttpHandlerFactory.h"
#include "wordDescriptionDownloader/WordDescriptionDownloaderFactory.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryFactory.h"

namespace glossary
{
GlossaryApplication::GlossaryApplication(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
    initialize();
}

void GlossaryApplication::initialize()
{
    std::unique_ptr<const dictionaryService::DictionaryServiceFactory> dictionaryServiceFactory =
        dictionaryService::DictionaryServiceFactory::createDictionaryServiceFactory(fileAccess);
    dictionaryService = dictionaryServiceFactory->createDictionaryService();

    dictionaryService->addDictionaryFromFile("base", utils::getProjectPath("glossary") +
                                                         "database/dictionaries/input.txt");

    std::unique_ptr<const webConnection::HttpHandlerFactory> httpHandlerFactory =
        webConnection::HttpHandlerFactory::createHttpHandlerFactory();
    std::shared_ptr<const webConnection::HttpHandler> httpHandler = httpHandlerFactory->createHttpHandler();

    std::unique_ptr<const wordDescriptionDownloader::WordDescriptionDownloaderFactory>
        wordDescriptionDownloaderFactory = wordDescriptionDownloader::WordDescriptionDownloaderFactory::
            createWordDescriptionDownloaderFactory(httpHandler);
    std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader =
        wordDescriptionDownloaderFactory->createWordDescriptionDownloader();

    std::unique_ptr<const wordDescriptionRepository::WordDescriptionRepositoryFactory>
        wordDescriptionRepositoryFactory = wordDescriptionRepository::WordDescriptionRepositoryFactory::
            createWordDescriptionRepositoryFactory(fileAccess);
    wordDescriptionRepository = wordDescriptionRepositoryFactory->createWordDescriptionRepository();

    wordDescriptionGenerator = std::make_unique<WordDescriptionConcurrentGenerator>(
        std::make_shared<DefaultWordDescriptionRetrieverService>(std::move(wordDescriptionDownloader),
                                                                 wordDescriptionRepository));

    std::unique_ptr<const statisticsRepository::StatisticsRepositoryFactory> statisticsRepositoryFactory =
        statisticsRepository::StatisticsRepositoryFactory::createStatisticsRepositoryFactory(fileAccess);
    statisticsRepository = statisticsRepositoryFactory->createStatisticsRepository();

    std::unique_ptr<const translationRepository::TranslationRepositoryFactory> translationRepositoryFactory =
        translationRepository::TranslationRepositoryFactory::createTranslationRepositoryFactory(fileAccess);
    translationRepository = translationRepositoryFactory->createTranslationRepository();

    std::unique_ptr<const translator::TranslatorFactory> translatorFactory =
        translator::TranslatorFactory::createTranslatorFactory(httpHandler);

    translationRetrieverService = std::make_shared<DefaultTranslationRetrieverService>(
        translatorFactory->createTranslator(), translationRepository);

    answerValidator = std::make_unique<DefaultAnswerValidator>();

    userPrompt = std::make_unique<UserStandardInputPrompt>();

    wordViewFormatter = std::make_unique<DefaultWordViewFormatter>();
}

void GlossaryApplication::run()
{
    wordDescriptionGenerator->generateWordsDescriptions(englishWords);
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
            guessWord();
            break;
        case 10:
            getEnglishWordDescription();
            break;
        case 11:
            showStatistics();
            break;
        case 12:
            resetStatistics();
            break;
        default:
            std::cout << "Invalid value\n";
        }
        std::cout << "Do you want to continue? (yes/no, y/n)\n";
        userWantsToContinue = answerValidator->validateYesAnswer(userPrompt->yesPrompt());
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
    std::cout << "9.Guess english word\n";
    std::cout << "10.Get word description\n";
    std::cout << "11.Show statistics\n";
    std::cout << "12.Reset statistics\n";
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

    // TODO: change generator into service
    const auto wordDescription =
        wordDescriptionGenerator->generateWordDescription(dictionaryWord->englishWord);
    std::cout << wordViewFormatter->formatWordDescriptionView(wordDescription);
}

void GlossaryApplication::translate() const
{
    std::cout << "Insert polish word:\n";
    const auto textToTranslate = userPrompt->getStringInput();
    const auto translation = translationRetrieverService->retrieveTranslation(
        textToTranslate, translator::SourceLanguage::Polish, translator::TargetLanguage::English);
    if (translation)
    {
        std::cout << *translation << "\n";
    }
    else
    {
        std::cout << "no translation\n";
    }
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
}

void GlossaryApplication::getEnglishWordDescription() const
{
    std::cout << "Insert english word:\n";
    const auto dictionaryWord = userPrompt->getStringInput();
    const auto wordDescription = wordDescriptionGenerator->generateWordDescription(dictionaryWord);
    std::cout << wordViewFormatter->formatWordDescriptionView(wordDescription) << "\n";
}

void GlossaryApplication::showStatistics() const
{
    std::cout << statisticsRepository->getStatistics() << "\n";
}

void GlossaryApplication::resetStatistics() const
{
    std::cout << "Not supported yet";
}

}