#include "GlossaryApplication.h"

#include <iostream>

#include "AnswerCheckerImpl.h"
#include "DescriptionParserImpl.h"
#include "DictionaryReaderImpl.h"
#include "GlossaryHtmlParserImpl.h"
#include "HttpWordDescriptionCreatorImpl.h"
#include "UserPromptImpl.h"
#include "WordDescriptionGeneratorImpl.h"
#include "WordDescriptionServiceImpl.h"
#include "WordRandomizerImpl.h"
#include "WordViewerImpl.h"
#include "statisticsDb/StatisticsDbFactory.h"
#include "utils/FileAccessImpl.h"
#include "webConnection/HttpHandlerFactory.h"
#include "wordsDescriptionsDb/WordsDescriptionsDbFactory.h"

GlossaryApplication::GlossaryApplication()
{
    initialize();
}

void GlossaryApplication::initialize()
{
    std::shared_ptr<const utils::FileAccess> fileAccess =
        std::make_shared<const utils::FileAccessImpl>();

    dictionaryReader = std::make_unique<DictionaryReaderImpl>(fileAccess);
    dictionary = dictionaryReader->read();

    std::unique_ptr<const wordsDescriptionsDb::WordsDescriptionsDbFactory>
        wordsDescriptionsDbFactory =
            wordsDescriptionsDb::WordsDescriptionsDbFactory::
                createWordsDescriptionsDbFactory(fileAccess);

    wordsDescriptionsDb =
        wordsDescriptionsDbFactory->createWordsDescriptionDb();

    std::unique_ptr<const webConnection::HttpHandlerFactory>
        httpHandlerFactory =
            webConnection::HttpHandlerFactory::createHttpHandlerFactory();

    std::shared_ptr<const webConnection::HttpHandler> httpHandler =
        httpHandlerFactory->createHttpHandler();
    std::unique_ptr<const GlossaryHtmlParser> htmlParser =
        std::make_unique<GlossaryHtmlParserImpl>();
    std::unique_ptr<const DescriptionParser> descriptionParser =
        std::make_unique<DescriptionParserImpl>();

    wordDescriptionGenerator = std::make_unique<WordDescriptionGeneratorImpl>(
        std::make_unique<WordDescriptionServiceImpl>(
            std::make_unique<HttpWordDescriptionCreatorImpl>(
                httpHandler, std::move(htmlParser),
                std::move(descriptionParser)),
            wordsDescriptionsDb));

    std::unique_ptr<const statisticsDb::StatisticsDbFactory>
        statisticsDbFactory =
            statisticsDb::StatisticsDbFactory::createStatisticsDbFactory(
                fileAccess);

    statisticsDb = statisticsDbFactory->createStatisticsDb();

    answerChecker = std::make_unique<AnswerCheckerImpl>();

    userPrompt = std::make_unique<UserPromptImpl>();

    viewer = std::make_unique<WordViewerImpl>();

    wordsRandomizer = std::make_unique<WordRandomizerImpl>();
}

void GlossaryApplication::run()
{
    for (const auto& dictWord : dictionary)
    {
        englishWords.push_back(dictWord.translatedText);
    }

    const auto wordsDescriptions =
        wordDescriptionGenerator->generateWordsDescriptions(englishWords);

    for (size_t index = 0; index < wordsDescriptions.size(); index++)
    {
        glossaryWords.push_back({dictionary[index].sourceText,
                                 dictionary[index].translatedText,
                                 wordsDescriptions[index]});
    }

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
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << e.what();
            break;
        }
        std::cout << viewer->viewPolishWord(word.polishWord);
        std::cout << "Insert english translation:\n";

        if (word.wordDescription &&
            answerChecker->correctWordAnswer(userPrompt->getInput(),
                                             word.wordDescription->englishWord))
        {
            std::cout << "Correct answer!\n";
            statisticsDb->addCorrectAnswer(word.wordDescription->englishWord);
        }
        else
        {
            std::cout << "Inorrect answer :(\n";
            statisticsDb->addIncorrectAnswer(word.wordDescription->englishWord);
        }

        std::cout << viewer->viewWord(word);

        std::cout << "Do you want to continue? (yes/no, y/n)\n";
        userWantToContinue = answerChecker->yesAnswer(userPrompt->yesPrompt());
    }
}
