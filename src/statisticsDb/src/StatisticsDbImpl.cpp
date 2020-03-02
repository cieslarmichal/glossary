#include "StatisticsDbImpl.h"
#include "plog/Log.h"

namespace statisticsDb
{

StatisticsDbImpl::StatisticsDbImpl(std::unique_ptr<StatisticsStorage> storageInit)
    : storage{std::move(storageInit)}
{
}

boost::optional<WordStatistics> StatisticsDbImpl::getWordStatistics(const EnglishWord& englishWord) const
{
    LOG_DEBUG << "Getting word statistics for "<< englishWord;
    return storage->getWordStatistics(englishWord);
}

Statistics StatisticsDbImpl::getStatistics() const
{
    LOG_DEBUG << "Getting statistics for all words";
    return storage->getStatistics();
}

void StatisticsDbImpl::addWordStatistics(WordStatistics wordStatistics)
{
    LOG_DEBUG << "Adding word statistics: "<< wordStatistics;
    storage->addWordStatistics(std::move(wordStatistics));
}

void StatisticsDbImpl::addCorrectAnswer(const EnglishWord& englishWord)
{
    LOG_DEBUG << "Adding correct answer for: "<< englishWord;
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addCorrectAnswer(englishWord);
}

void StatisticsDbImpl::addIncorrectAnswer(const EnglishWord& englishWord)
{
    LOG_DEBUG << "Adding incorrect answer for: "<< englishWord;
    if (not storage->contains(englishWord))
    {
        addEmptyWordStatistics(englishWord);
    }
    storage->addIncorrectAnswer(englishWord);
}

void StatisticsDbImpl::resetStatistics()
{
    LOG_DEBUG << "Clearing statistics";
    storage->resetStatistics();
}

void StatisticsDbImpl::addEmptyWordStatistics(const EnglishWord& englishWord) const
{
    storage->addWordStatistics(WordStatistics{englishWord, 0, 0});
}

}