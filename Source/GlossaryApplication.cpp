#include "GlossaryApplication.h"

#include <iostream>
#include <statisticsDb/StatisticsPersistentStorage.h>

#include "AnswerCheckerImpl.h"
#include "UserPromptImpl.h"
#include "WordRandomizerImpl.h"
#include "WordViewerImpl.h"
#include "WordsGeneratorServiceImpl.h"
#include "utils/FileAccessImpl.h"
#include "statisticsDb/StatisticsDbImpl.h"
#include "statisticsDb/StatisticsSerializerImpl.h"

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
    std::shared_ptr<const statisticsDb::StatisticsSerializer>
        serializer = std::make_shared<
            const statisticsDb::StatisticsSerializerImpl>();
    std::unique_ptr<statisticsDb::StatisticsStorage> storage =
        std::make_unique<statisticsDb::StatisticsPersistentStorage>(
            fileAccess, serializer);
    answersCounter = std::make_unique<statisticsDb::StatisticsDbImpl>(
        std::move(storage));

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
        WordDescription word;
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

        if (answerChecker->correctWordAnswer(userPrompt->getInput(),
                                             word.englishWord))
        {
            std::cout << "Correct answer!\n";
            answersCounter->addCorrectAnswer(word.englishWord);
        }
        else
        {
            std::cout << "Inorrect answer :(\n";
            answersCounter->addIncorrectAnswer(word.englishWord);
        }

        std::cout << viewer->viewWord(word);

        std::cout << "Do you want to continue? (yes/no, y/n)\n";
        userWantToContinue = answerChecker->yesAnswer(userPrompt->yesPrompt());
    }
}
