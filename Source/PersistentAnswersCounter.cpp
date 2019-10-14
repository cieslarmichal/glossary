#include <Exceptions/FileNotFound.h>
#include <iostream>
#include "PersistentAnswersCounter.h"

const std::string PersistentAnswersCounter::fileDirectory{"../database"};
const std::string PersistentAnswersCounter::fileName{"/answersStatistics.txt"};
const std::string PersistentAnswersCounter::filePath{fileDirectory + fileName};

PersistentAnswersCounter::PersistentAnswersCounter(std::shared_ptr<const FileAccess> fileAccessInit,
                                                   std::shared_ptr<const AnswersStatisticsSerializer> serializerInit)
        : fileAccess{fileAccessInit}, serializer{serializerInit}
{
    loadFile();
}

void PersistentAnswersCounter::addCorrectAnswer(const EnglishWord& englishWord)
{
    if (not containsWord(englishWord))
    {
        addEmptyStatisticsPerWord(englishWord);
    }

    statistics.at(englishWord).addCorrectAnswer();
    serialize();
}


void PersistentAnswersCounter::addIncorrectAnswer(const EnglishWord& englishWord)
{
    if (not containsWord(englishWord))
    {
        addEmptyStatisticsPerWord(englishWord);
    }

    statistics.at(englishWord).addIncorrectAnswer();
    serialize();
}

boost::optional<AnswersStatisticsPerWord>
PersistentAnswersCounter::getAnswersStatisticsPerWord(const EnglishWord& englishWord) const
{
    if (containsWord(englishWord))
    {
        return statistics.at(englishWord);
    }
    return boost::none;
}

AnswersStatistics PersistentAnswersCounter::getAnswersStatistics() const
{
    return statistics;
}

void PersistentAnswersCounter::loadFile()
{
    try
    {
        statistics = serializer->deserialize(fileAccess->readContent(filePath));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
        return;
    }
}

void PersistentAnswersCounter::serialize() const
{
    try
    {
        fileAccess->write(filePath, serializer->serialize(statistics));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
    }
}

bool PersistentAnswersCounter::containsWord(const EnglishWord& englishWord) const
{
    return statistics.count(englishWord);
}

void PersistentAnswersCounter::addEmptyStatisticsPerWord(const EnglishWord& englishWord)
{
    statistics[englishWord] = AnswersStatisticsPerWord{englishWord};
}

