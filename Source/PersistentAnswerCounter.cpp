#include "PersistentAnswerCounter.h"

PersistentAnswerCounter::PersistentAnswerCounter(std::shared_ptr<const FileAccess> fileAccessInit)
        : fileAccess{fileAccessInit}
{
    loadFile();
}

void PersistentAnswerCounter::addCorrectAnswer() const
{

}

void PersistentAnswerCounter::addIncorrectAnswer() const
{

}

void PersistentAnswerCounter::loadFile()
{

}

void PersistentAnswerCounter::serialize() const
{

}

