#include "GlossaryApplication.h"

#include "WordsGeneratorServiceImpl.h"
#include "PersistentAnswersCounter.h"
#include "WordViewerImpl.h"
#include "AnswerCheckerImpl.h"
#include "UserPromptImpl.h"
#include "AnswersStatisticsSerializerImpl.h"
#include "FileAccessImpl.h"
#include "WordRandomizerImpl.h"

GlossaryApplication::GlossaryApplication()
{
    initialize();
}

//TODO: make FileAccessImpl only one shared_ptr not two
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

}
