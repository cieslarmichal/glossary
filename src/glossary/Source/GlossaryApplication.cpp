#include "GlossaryApplication.h"

#include <iostream>

#include "DefaultAnswerValidator.h"
#include "DefaultTranslationRetrieverService.h"
#include "DefaultWordDescriptionRetrieverService.h"
#include "DefaultWordRandomizer.h"
#include "DefaultWordViewFormatter.h"
#include "DefaultWordsMerger.h"
#include "UserStandardInputPrompt.h"
#include "WordDescriptionConcurrentGenerator.h"
#include "dictionaryRepository/DictionaryRepositoryFactory.h"
#include "statisticsRepository/StatisticsRepositoryFactory.h"
#include "translationRepository/TranslationRepositoryFactory.h"
#include "translator/TranslatorFactory.h"
#include "utils/GetProjectPath.h"
#include "utils/RandomNumberMersenneTwisterGenerator.h"
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
    std::unique_ptr<const dictionaryRepository::DictionaryRepositoryFactory> dictionaryRepositoryFactory =
        dictionaryRepository::DictionaryRepositoryFactory::createDictionaryRepositoryFactory(fileAccess);
    dictionaryRepository = dictionaryRepositoryFactory->createDictionaryRepository();

    dictionaryRepository->addDictionaryFromFile("base", utils::getProjectPath("glossary") +
                                                            "database/dictionaries/input.txt");
    dictionaries = dictionaryRepository->getDictionaries();

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

    wordsRandomizer = std::make_unique<DefaultWordRandomizer>(
        std::make_shared<utils::RandomNumberMersenneTwisterGenerator>());

    wordsMerger = std::make_unique<DefaultWordsMerger>();
}

void GlossaryApplication::run()
{
    auto baseDict = std::find_if(dictionaries.begin(), dictionaries.end(),
                                 [](const auto& dictionary) { return dictionary.name == "base"; });
    if (baseDict == dictionaries.end())
    {
        std::cerr << "not found base dictionary";
        return;
    }

    for (const auto& dictWord : baseDict->words)
    {
        englishWords.push_back(dictWord.englishWord);
    }

    const auto wordsDescriptions = wordDescriptionGenerator->generateWordsDescriptions(englishWords);

    glossaryWords = wordsMerger->mergeWords(baseDict->words, wordsDescriptions);

    for (const auto& glossaryWord : glossaryWords)
    {
        if (glossaryWord->polishTranslation)
        {
            wordsWithTranslation.emplace_back(*glossaryWord);
        }
    }

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
        default:
            std::cout << "Invalid value\n";
        }
        std::cout << "Do you want to continue? (yes/no, y/n)\n";
        userWantsToContinue = answerValidator->validateYesAnswer(userPrompt->yesPrompt());
    }
}

boost::optional<Word> GlossaryApplication::randomizeWord(const Words& words) const
{
    try
    {
        return wordsRandomizer->randomizeWord(words);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what();
    }
    return boost::none;
}

boost::optional<Word> GlossaryApplication::randomizeWordWithTranslation() const
{
    if (wordsWithTranslation.empty())
    {
        return boost::none;
    }
    return randomizeWord(wordsWithTranslation);
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
}

void GlossaryApplication::guessWord() const
{
    const auto& randomizedWord = randomizeWordWithTranslation();
    if (randomizedWord == boost::none || randomizedWord->polishTranslation == boost::none)
    {
        std::cerr << "No words with translations available";
        return;
    }
    std::cout << wordViewFormatter->formatPolishWordView(*randomizedWord->polishTranslation);
    std::cout << "Insert english translation:\n";

    if (answerValidator->validateAnswer(userPrompt->getStringInput(), randomizedWord->englishWord))
    {
        std::cout << "Correct answer!\n";
        statisticsRepository->addCorrectAnswer(randomizedWord->englishWord);
    }
    else
    {
        std::cout << "Incorrect answer :(\n";
        statisticsRepository->addIncorrectAnswer(randomizedWord->wordDescription->englishWord);
    }

    std::cout << wordViewFormatter->formatWordView(*randomizedWord);
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
    dictionaries = dictionaryRepository->getDictionaries();
    for (const auto& dictionary : dictionaries)
    {
        std::cout << dictionary.name << " ";
    }
    std::cout << "\n";
}

void GlossaryApplication::listDictionaryWordsFromDictionary()
{
    dictionaries = dictionaryRepository->getDictionaries();
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    auto foundDictionary =
        std::find_if(dictionaries.begin(), dictionaries.end(),
                     [&dictionaryName](const auto& dictionary) { return dictionary.name == dictionaryName; });
    if (foundDictionary != dictionaries.end())
        std::cout << foundDictionary->words << "\n";
    else
        std::cout << "Dictionary not found\n";
}

void GlossaryApplication::addDictionary() const
{
    std::cout << "Insert dictionary name to add:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    if (not dictionaryRepository->containsDictionary(dictionaryName))
        dictionaryRepository->addDictionary(dictionaryName);
    else
        std::cout << "Dictionary: " << dictionaryName << " already exists\n";
}

void GlossaryApplication::addEnglishWordToDictionary() const
{
    std::cout << "Insert dictionary name:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    if (dictionaryRepository->containsDictionary(dictionaryName))
    {
        std::cout << "Insert english word:\n";
        const auto englishWord = userPrompt->getStringInput();
        dictionaryRepository->addWordToDictionary({englishWord, boost::none}, dictionaryName);
    }
    else
        std::cout << "Dictionary: " << dictionaryName << " not found\n";
}

void GlossaryApplication::removeDictionary() const
{
    std::cout << "Insert dictionary name to remove:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    if (dictionaryRepository->containsDictionary(dictionaryName))
        dictionaryRepository->removeDictionary(dictionaryName);
    else
        std::cout << "Dictionary: " << dictionaryName << " not found\n";
}

void GlossaryApplication::removeEnglishWordFromDictionary() const
{
    std::cout << "Insert dictionary name to remove word from:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    if (dictionaryRepository->containsDictionary(dictionaryName))
    {
        std::cout << "Insert english word:\n";
        const auto englishWord = userPrompt->getStringInput();
        dictionaryRepository->removeWordFromDictionary(englishWord, dictionaryName);
    }
    else
        std::cout << "Dictionary: " << dictionaryName << " not found\n";
}

void GlossaryApplication::addDictionaryFromFile() const
{
    std::cout << "Insert dictionary name to add:\n";
    const auto dictionaryName = userPrompt->getStringInput();
    std::cout << "Insert absolute path to words dictionary file(csv format):\n";
    const auto pathToFileWithDictionaryWords = userPrompt->getStringInput();
    dictionaryRepository->addDictionaryFromFile(dictionaryName, pathToFileWithDictionaryWords);
}

void GlossaryApplication::getEnglishWordDescription() const
{
    std::cout << "Insert english word:\n";
    const auto dictionaryWord = userPrompt->getStringInput();
    std::cout << wordDescriptionGenerator->generateWordDescription(dictionaryWord);
}

void GlossaryApplication::showStatistics() const
{
    std::cout << statisticsRepository->getStatistics() << "\n";
}
}