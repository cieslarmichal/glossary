#include "GlossaryApplication.h"

#include <iostream>

#include "../../dictionaryRepository/src/DictionaryWordsTextFileReader.h"
#include "DefaultAnswerValidator.h"
#include "DefaultStatisticsModifierService.h"
#include "DefaultTranslationRetrieverService.h"
#include "DefaultWordDescriptionRetrieverService.h"
#include "DefaultWordViewFormatter.h"
#include "DefaultWordsMerger.h"
#include "UserStandardInputPrompt.h"
#include "WordDescriptionConcurrentGenerator.h"
#include "WordMersenneTwisterRandomizer.h"
#include "statisticsRepository/StatisticsRepositoryFactory.h"
#include "translationRepository/TranslationRepositoryFactory.h"
#include "translator/TranslatorFactory.h"
#include "utils/StlOperators.h"
#include "webConnection/HttpHandlerFactory.h"
#include "wordDescriptionDownloader/WordDescriptionDownloaderFactory.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryFactory.h"

GlossaryApplication::GlossaryApplication(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{

    initialize();
}

void GlossaryApplication::initialize()
{
    dictionaryReader = std::make_unique<DefaultDictionaryReader>(fileAccess);
    dictionaries = dictionaryReader->readDictionaries();
    baseDictionary = dictionaries.at("base");

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
    statisticsModifierService = std::make_shared<DefaultStatisticsModifierService>(statisticsRepository);

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

    wordsRandomizer = std::make_unique<WordMersenneTwisterRandomizer>();

    wordsMerger = std::make_unique<DefaultWordsMerger>();
}

void GlossaryApplication::run()
{
    for (const auto& dictWord : baseDictionary)
    {
        englishWords.push_back(dictWord.translatedText);
    }

    const auto wordsDescriptions = wordDescriptionGenerator->generateWordsDescriptions(englishWords);

    glossaryWords = wordsMerger->mergeWords(baseDictionary, wordsDescriptions);

    loop();
}

void GlossaryApplication::loop()
{
    auto userWantToContinue = true;

    while (userWantToContinue)
    {
        showMenu();
        switch (userPrompt->getIntInput())
        {
        case 1:
            translate();
            break;
        case 2:
            std::cout << "Operation not supported yet\n";
            break;
        case 3:
        case 4:
            listDictionaries();
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            std::cout << "Operation not supported yet\n";
            break;
        case 10:
            guessWord();
            break;
        case 11:
        case 12:
            std::cout << "Operation not supported yet\n";
            break;
        default:
            std::cout << "Invalid value\n";
        }
        userWantToContinue = answerValidator->validateYesAnswer(userPrompt->yesPrompt());
    }
}

boost::optional<Word> GlossaryApplication::randomizeWord() const
{
    try
    {
        return wordsRandomizer->randomizeWord(glossaryWords);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what();
    }
    return boost::none;
}

void GlossaryApplication::showMenu() const
{
    std::cout << "Choose glossary mode:\n";
    std::cout << "1.Translation\n";
    std::cout << "2.Add word to dictionary\n";
    std::cout << "3.List dictionaries\n";
    std::cout << "4.List english words from dictionary\n";
    std::cout << "5.Add dictionary\n";
    std::cout << "6.Add english word to dictionary\n";
    std::cout << "7.Remove dictionary\n";
    std::cout << "8.Remove english word from dictionary\n";
    std::cout << "9.Add dictionary from file\n";
    std::cout << "10.Guess english word\n";
    std::cout << "11.Get description from english word\n";
    std::cout << "12.Display statistics\n";
}

void GlossaryApplication::guessWord() const
{
    const auto& randomizedWord = randomizeWord();
    if (randomizedWord == boost::none)
    {
        std::cerr << "Error while randomizing word:";
        return;
    }
    std::cout << wordViewFormatter->formatPolishWordView(randomizedWord->polishWord);
    std::cout << "Insert english translation:\n";

    if (randomizedWord->wordDescription &&
        answerValidator->validateAnswer(userPrompt->getStringInput(),
                                        randomizedWord->wordDescription->englishWord))
    {
        std::cout << "Correct answer!\n";
        statisticsModifierService->addCorrectAnswer(randomizedWord->wordDescription->englishWord);
    }
    else
    {
        std::cout << "Inorrect answer :(\n";
        statisticsModifierService->addIncorrectAnswer(randomizedWord->wordDescription->englishWord);
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

void GlossaryApplication::listDictionaries() const
{
    std::cout << dictionaries << "\n";
}
