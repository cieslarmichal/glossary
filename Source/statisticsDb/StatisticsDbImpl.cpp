#include "statisticsDb/StatisticsDbImpl.h"

namespace statisticsDb
{

StatisticsDbImpl::StatisticsDbImpl(
    std::unique_ptr<StatisticsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

boost::optional<WordStatistics>
StatisticsDbImpl::getWordStatistics(const EnglishWord& englishWord) const
{
    return storage->getWordStatistics(englishWord);
}

Statistics StatisticsDbImpl::getStatistics() const
{
    return storage->getStatistics();
}

void StatisticsDbImpl::addWordStatistics(WordStatistics wordStatistics)
{
    storage->addWordStatistics(std::move(wordStatistics));
}

void StatisticsDbImpl::addCorrectAnswer(const EnglishWord& englishWord)
{
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addCorrectAnswer(englishWord);
}

void StatisticsDbImpl::addIncorrectAnswer(const EnglishWord& englishWord)
{
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addIncorrectAnswer(englishWord);
}

void StatisticsDbImpl::resetStatistics()
{
    storage->resetStatistics();
}

void StatisticsDbImpl::addEmptyWordStatistics(
    const EnglishWord& englishWord) const
{
    storage->addWordStatistics(WordStatistics{englishWord, 0, 0});
}

}