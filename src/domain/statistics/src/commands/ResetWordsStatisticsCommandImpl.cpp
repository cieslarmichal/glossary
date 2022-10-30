#include "ResetWordsStatisticsCommandImpl.h"

namespace glossary::statistics
{
ResetWordsStatisticsCommandImpl::ResetWordsStatisticsCommandImpl(
    std::shared_ptr<StatisticsRepository> statisticsRepositoryInit)
    : statisticsRepository{std::move(statisticsRepositoryInit)}
{
}

void ResetWordsStatisticsCommandImpl::resetWordsStatistics()
{
    statisticsRepository->resetStatistics();
}
}
