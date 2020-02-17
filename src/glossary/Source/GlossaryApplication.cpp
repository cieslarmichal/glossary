#include "GlossaryApplication.h"

#include <iostream>

#include "AnswerCheckerImpl.h"
#include "UserPromptImpl.h"
#include "WordRandomizerImpl.h"
#include "WordViewerImpl.h"
#include "WordsGeneratorServiceImpl.h"
#include "statisticsDb/StatisticsDbFactory.h"
#include "utils/FileAccessImpl.h"

GlossaryApplication::GlossaryApplication()
{
    initialize();
}

// TODO: make FileAccessImpl only one shared_ptr not two
// TODO: (persistentAnswersCounter and WordService)
void GlossaryApplication::initialize()
{
    wordsGenerator = std::make_unique<WordsGeneratorServiceImpl>();

    std::shared_ptr<const utils::FileAccess> fileAccess =
        std::make_shared<const utils::FileAccessImpl>();

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
    glossaryWords = wordsGenerator->generateWords();

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
            word =
                wordsRandomizer->randomizeWord(glossaryWords);
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
            statisticsDb->addIncorrectAnswer(
                word.wordDescription->englishWord);
        }

        std::cout << viewer->viewWord(word);

        std::cout << "Do you want to continue? (yes/no, y/n)\n";
        userWantToContinue = answerChecker->yesAnswer(userPrompt->yesPrompt());
    }
}
