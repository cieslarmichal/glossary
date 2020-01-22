#include "GlossaryApplication.h"

#include <iostream>

#include "AnswerCheckerImpl.h"
#include "FileAccessImpl.h"
#include "UserPromptImpl.h"
#include "WordRandomizerImpl.h"
#include "WordViewerImpl.h"
#include "WordsGeneratorServiceImpl.h"
#include "wordsDb/statisticsDb/StatisticsDbImpl.h"
#include "wordsDb/statisticsDb/StatisticsSerializerImpl.h"

GlossaryApplication::GlossaryApplication()
{
    initialize();
}

// TODO: make FileAccessImpl only one shared_ptr not two
// (persistentAnswersCounter and WordService)
void GlossaryApplication::initialize()
{
    wordsGenerator = std::make_unique<WordsGeneratorServiceImpl>();

    std::shared_ptr<const FileAccess> fileAccess =
        std::make_shared<const FileAccessImpl>();
    std::shared_ptr<const wordsDb::statisticsDb::StatisticsSerializer> serializer =
        std::make_shared<const wordsDb::statisticsDb::StatisticsSerializerImpl>();
    answersCounter =
        std::make_unique<wordsDb::statisticsDb::StatisticsDbImpl>(fileAccess, serializer);

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
