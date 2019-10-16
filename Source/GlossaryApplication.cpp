#include "GlossaryApplication.h"

#include "WordsGeneratorServiceImpl.h"
#include "PersistentAnswersCounter.h"
#include "WordViewerImpl.h"
#include "AnswerCheckerImpl.h"
#include "UserPromptImpl.h"
#include "AnswersStatisticsSerializerImpl.h"
#include "FileAccessImpl.h"
#include "WordRandomizerImpl.h"
#include <iostream>

GlossaryApplication::GlossaryApplication()
{
    initialize();
}

//TODO: make FileAccessImpl only one shared_ptr not two (persistentAnswersCounter and WordService)
void GlossaryApplication::initialize()
{
    wordsGenerator = std::make_unique<WordsGeneratorServiceImpl>();

    std::shared_ptr<const FileAccess> fileAccess = std::make_shared<const FileAccessImpl>();
    std::shared_ptr<const AnswersStatisticsSerializer> serializer = std::make_shared<const AnswersStatisticsSerializerImpl>();
    answersCounter = std::make_unique<PersistentAnswersCounter>(fileAccess, serializer);

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

    while(userWantToContinue)
    {
        const auto word = wordsRandomizer->randomizeWord(glossaryWords);
        std::cout << viewer->viewEnglishWord(word.englishWord);

        if(answerChecker->correctWordAnswer(userPrompt->getInput(), word.englishWord))
        {
            answersCounter->addCorrectAnswer(word.englishWord);
        }
        else
        {
            answersCounter->addIncorrectAnswer(word.englishWord);
        }

        std::cout<<viewer->viewWord(word);

        userWantToContinue = answerChecker->yesAnswer(userPrompt->yesPrompt());
    }


}