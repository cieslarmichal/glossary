#include "DefaultStatisticsRepository.h"

namespace glossary::statistics
{
DefaultStatisticsRepository::DefaultStatisticsRepository(std::unique_ptr<StatisticsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

std::optional<WordStatistics>
DefaultStatisticsRepository::getWordStatistics(const std::string& englishWord) const
{
    return storage->getWordStatistics(englishWord);
}

std::vector<WordStatistics> DefaultStatisticsRepository::getStatistics() const
{
    return storage->getStatistics();
}

void DefaultStatisticsRepository::addWordStatistics(WordStatistics wordStatistics)
{
    storage->addWordStatistics(std::move(wordStatistics));
}

void DefaultStatisticsRepository::addCorrectAnswer(const std::string& englishWord)
{
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addCorrectAnswer(englishWord);
}

void DefaultStatisticsRepository::addIncorrectAnswer(const std::string& englishWord)
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

void DefaultStatisticsRepository::addEmptyWordStatistics(const std::string& englishWord) const
{
    storage->addWordStatistics(WordStatistics{englishWord, 0, 0});
}

}