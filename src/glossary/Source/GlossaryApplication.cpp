#include "GlossaryApplication.h"

#include <iostream>

#include "DefaultAnswerValidator.h"
#include "DefaultDictionaryReader.h"
#include "DefaultWordDescriptionService.h"
#include "DefaultWordViewFormatter.h"
#include "DefaultWordsMerger.h"
#include "UserStandardInputPrompt.h"
#include "WordDescriptionConcurrentGenerator.h"
#include "WordMersenneTwisterRandomizer.h"
#include "statisticsRepository/StatisticsRepositoryFactory.h"
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

    std::unique_ptr<const wordDescriptionRepository::WordDescriptionRepositoryFactory>
        wordsDescriptionsDbFactory = wordDescriptionRepository::WordDescriptionRepositoryFactory::
            createWordDescriptionRepositoryFactory(fileAccess);

    wordDescriptionRepository = wordsDescriptionsDbFactory->createWordDescriptionRepository();

    std::unique_ptr<const webConnection::HttpHandlerFactory> httpHandlerFactory =
        webConnection::HttpHandlerFactory::createHttpHandlerFactory();

    std::shared_ptr<const webConnection::HttpHandler> httpHandler = httpHandlerFactory->createHttpHandler();

    std::unique_ptr<const wordDescriptionDownloader::WordDescriptionDownloaderFactory>
        wordDescriptionDownloaderFactory = wordDescriptionDownloader::WordDescriptionDownloaderFactory::
            createWordDescriptionDownloaderFactory(httpHandler);
    std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader =
        wordDescriptionDownloaderFactory->createWordDescriptionDownloader();

    wordDescriptionGenerator =
        std::make_unique<WordDescriptionConcurrentGenerator>(std::make_unique<DefaultWordDescriptionService>(
            std::move(wordDescriptionDownloader), wordDescriptionRepository));

    std::unique_ptr<const statisticsRepository::StatisticsRepositoryFactory> statisticsRepositoryFactory =
        statisticsRepository::StatisticsRepositoryFactory::createStatisticsRepositoryFactory(fileAccess);

    statisticsRepository = statisticsRepositoryFactory->createStatisticsRepository();

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
        const auto &randomizedWord = randomizeWord();
        if(randomizedWord == boost::none)
        {
            std::cerr << "Error while randomizing word:";
            break;
        }
        std::cout << wordViewFormatter->formatPolishWordView(randomizedWord->polishWord);
        std::cout << "Insert english translation:\n";

        if (randomizedWord->wordDescription &&
            answerValidator->validateAnswer(userPrompt->getInput(), randomizedWord->wordDescription->englishWord))
        {
            std::cout << "Correct answer!\n";
            statisticsRepository->addCorrectAnswer(randomizedWord->wordDescription->englishWord);
        }
        else
        {
            std::cout << "Inorrect answer :(\n";
            statisticsRepository->addIncorrectAnswer(randomizedWord->wordDescription->englishWord);
        }

        std::cout << wordViewFormatter->formatWordView(*randomizedWord);

        std::cout << "Do you want to continue? (yes/no, y/n)\n";
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
