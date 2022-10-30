#include "GetWordsStatisticsQueryImpl.h"

namespace glossary::statistics
{
GetWordsStatisticsQueryImpl::GetWordsStatisticsQueryImpl(std::shared_ptr<StatisticsRepository> statisticsRepositoryInit)
    : statisticsRepository{std::move(statisticsRepositoryInit)}
{
}

std::vector<WordStatistics> GetWordsStatisticsQueryImpl::getWordsStatistics()
{
    return statisticsRepository->getStatistics();
}
}
