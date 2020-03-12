#include "GlossaryApplication.h"

#include <iostream>

#include "AnswerCheckerImpl.h"
#include "DescriptionParserImpl.h"
#include "DictionaryReaderImpl.h"
#include "GlossaryHtmlParserImpl.h"
#include "HttpWordDescriptionCreatorImpl.h"
#include "UserPromptImpl.h"
#include "WordDescriptionConcurrentGenerator.h"
#include "WordDescriptionServiceImpl.h"
#include "WordRandomizerImpl.h"
#include "WordViewerImpl.h"
#include "WordsBuilderImpl.h"
#include "statisticsDb/StatisticsDbFactory.h"
#include "webConnection/HttpHandlerFactory.h"
#include "wordsDescriptionsDb/WordsDescriptionsDbFactory.h"

GlossaryApplication::GlossaryApplication(std::shared_ptr<utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
    initialize();
}

void GlossaryApplication::initialize()
{
    dictionaryReader = std::make_unique<DictionaryReaderImpl>(fileAccess);
    dictionary = dictionaryReader->read();

    std::unique_ptr<const wordsDescriptionsDb::WordsDescriptionsDbFactory> wordsDescriptionsDbFactory =
        wordsDescriptionsDb::WordsDescriptionsDbFactory::createWordsDescriptionsDbFactory(fileAccess);

    wordsDescriptionsDb = wordsDescriptionsDbFactory->createWordsDescriptionDb();

    std::unique_ptr<const webConnection::HttpHandlerFactory> httpHandlerFactory =
        webConnection::HttpHandlerFactory::createHttpHandlerFactory();

    std::shared_ptr<const webConnection::HttpHandler> httpHandler = httpHandlerFactory->createHttpHandler();
    std::unique_ptr<const GlossaryHtmlParser> htmlParser = std::make_unique<GlossaryHtmlParserImpl>();
    std::unique_ptr<const DescriptionParser> descriptionParser = std::make_unique<DescriptionParserImpl>();

    wordDescriptionGenerator =
        std::make_unique<WordDescriptionConcurrentGenerator>(std::make_unique<WordDescriptionServiceImpl>(
            std::make_unique<HttpWordDescriptionCreatorImpl>(httpHandler, std::move(htmlParser),
                                                             std::move(descriptionParser)),
            wordsDescriptionsDb));

    std::unique_ptr<const statisticsDb::StatisticsDbFactory> statisticsDbFactory =
        statisticsDb::StatisticsDbFactory::createStatisticsDbFactory(fileAccess);

    statisticsDb = statisticsDbFactory->createStatisticsDb();

    answerChecker = std::make_unique<AnswerCheckerImpl>();

    userPrompt = std::make_unique<UserPromptImpl>();

    viewer = std::make_unique<WordViewerImpl>();

    wordsRandomizer = std::make_unique<WordRandomizerImpl>();

    wordsBuilder = std::make_unique<WordsBuilderImpl>();
}

void GlossaryApplication::run()
{
    for (const auto& dictWord : dictionary)
    {
        englishWords.push_back(dictWord.translatedText);
    }

    const auto wordsDescriptions = wordDescriptionGenerator->generateWordsDescriptions(englishWords);

    glossaryWords = wordsBuilder->buildWords(dictionary, wordsDescriptions);

    loop();
}

void GlossaryApplication::loop()
{
    auto userWantToContinue = true;

    while (userWantToContinue)
    {
        Word word;
        try
        {
            word = wordsRandomizer->randomizeWord(glossaryWords);
            //            std::cerr<< "CURRENT WORD: "<<word<<"\n\n";
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << e.what();
            break;
        }
        std::cout << viewer->viewPolishWord(word.polishWord);
        std::cout << "Insert english translation:\n";
        std::cerr << "expected englishWord: " << word.wordDescription->englishWord << std::endl;

        if (word.wordDescription &&
            answerChecker->correctWordAnswer(userPrompt->getInput(), word.wordDescription->englishWord))
        {
            std::cout << "Correct answer!\n";
            statisticsDb->addCorrectAnswer(word.wordDescription->englishWord);
        }
        else
        {
            std::cout << "Inorrect answer :(\n";
            // TODO: nie dziala
            statisticsDb->addIncorrectAnswer(word.wordDescription->englishWord);
        }

        std::cout << viewer->viewWord(word);

        std::cout << "Do you want to continue? (yes/no, y/n)\n";
        userWantToContinue = answerChecker->yesAnswer(userPrompt->yesPrompt());
    }
}
