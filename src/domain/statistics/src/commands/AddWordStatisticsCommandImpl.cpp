#include "AddWordStatisticsCommandImpl.h"

namespace glossary::statistics
{
AddWordStatisticsCommandImpl::AddWordStatisticsCommandImpl(
    std::shared_ptr<StatisticsRepository> statisticsRepositoryInit)
    : statisticsRepository{std::move(statisticsRepositoryInit)}
{
}

void AddWordStatisticsCommandImpl::addWordStatistics(const WordStatistics& wordStatistics)
{
    statisticsRepository->addWordStatistics(wordStatistics);
}
}
