#include "DefaultStatisticsDb.h"

namespace statisticsDb
{

DefaultStatisticsDb::DefaultStatisticsDb(std::unique_ptr<StatisticsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

boost::optional<WordStatistics> DefaultStatisticsDb::getWordStatistics(const EnglishWord& englishWord) const
{
    return storage->getWordStatistics(englishWord);
}

Statistics DefaultStatisticsDb::getStatistics() const
{
    return storage->getStatistics();
}

void DefaultStatisticsDb::addWordStatistics(WordStatistics wordStatistics)
{
    storage->addWordStatistics(std::move(wordStatistics));
}

void DefaultStatisticsDb::addCorrectAnswer(const EnglishWord& englishWord)
{
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addCorrectAnswer(englishWord);
}

void DefaultStatisticsDb::addIncorrectAnswer(const EnglishWord& englishWord)
{
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addIncorrectAnswer(englishWord);
}

void DefaultStatisticsDb::resetStatistics()
{
    storage->resetStatistics();
}

void DefaultStatisticsDb::addEmptyWordStatistics(const EnglishWord& englishWord) const
{
    storage->addWordStatistics(WordStatistics{englishWord, 0, 0});
}

}