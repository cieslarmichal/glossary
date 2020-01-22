#include "wordsDb/statisticsDb/StatisticsDbImpl.h"

#include <iostream>

#include "exceptions/FileNotFound.h"

namespace wordsDb::statisticsDb
{

const std::string StatisticsDbImpl::fileDirectory{"../database"};
const std::string StatisticsDbImpl::fileName{"/answersStatistics.txt"};
const std::string StatisticsDbImpl::filePath{fileDirectory + fileName};

StatisticsDbImpl::StatisticsDbImpl(
    std::shared_ptr<const FileAccess> fileAccessInit,
    std::shared_ptr<const StatisticsSerializer> serializerInit)
    : fileAccess{fileAccessInit}, serializer{serializerInit}
{
    loadFile();
}

void StatisticsDbImpl::addCorrectAnswer(const EnglishWord& englishWord)
{
    if (not containsWord(englishWord))
    {
        addEmptyStatisticsPerWord(englishWord);
    }

    statistics.at(englishWord).addCorrectAnswer();
    serialize();
}

void StatisticsDbImpl::addIncorrectAnswer(const EnglishWord& englishWord)
{
    if (not containsWord(englishWord))
    {
        addEmptyStatisticsPerWord(englishWord);
    }

    statistics.at(englishWord).addIncorrectAnswer();
    serialize();
}

boost::optional<AnswersStatisticsPerWord>
StatisticsDbImpl::getAnswersStatisticsPerWord(
    const EnglishWord& englishWord) const
{
    if (containsWord(englishWord))
    {
        return statistics.at(englishWord);
    }
    return boost::none;
}

AnswersStatistics StatisticsDbImpl::getAnswersStatistics() const
{
    return statistics;
}

void StatisticsDbImpl::loadFile()
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

void StatisticsDbImpl::serialize() const
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

bool StatisticsDbImpl::containsWord(const EnglishWord& englishWord) const
{
    return statistics.count(englishWord);
}

void StatisticsDbImpl::addEmptyStatisticsPerWord(const EnglishWord& englishWord)
{
    statistics[englishWord] = AnswersStatisticsPerWord{englishWord};
}
}