#include "DefaultStatisticsRepository.h"

namespace glossary::statisticsRepository
{
DefaultStatisticsRepository::DefaultStatisticsRepository(std::unique_ptr<StatisticsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

boost::optional<WordStatistics>
DefaultStatisticsRepository::getWordStatistics(const EnglishWord& englishWord) const
{
    return storage->getWordStatistics(englishWord);
}

Statistics DefaultStatisticsRepository::getStatistics() const
{
    return storage->getStatistics();
}

void DefaultStatisticsRepository::addWordStatistics(WordStatistics wordStatistics)
{
    storage->addWordStatistics(std::move(wordStatistics));
}

void DefaultStatisticsRepository::addCorrectAnswer(const EnglishWord& englishWord)
{
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addCorrectAnswer(englishWord);
}

void DefaultStatisticsRepository::addIncorrectAnswer(const EnglishWord& englishWord)
{
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addIncorrectAnswer(englishWord);
}

void DefaultStatisticsRepository::resetStatistics()
{
    storage->resetStatistics();
}

void DefaultStatisticsRepository::addEmptyWordStatistics(const EnglishWord& englishWord) const
{
    storage->addWordStatistics(WordStatistics{englishWord, 0, 0});
}

}