#include "DefaultStatisticsRepositoryFactory.h"

#include "DefaultStatisticsRepository.h"
#include "StatisticsJsonSerializer.h"
#include "StatisticsPersistentStorage.h"

namespace statisticsRepository
{

DefaultStatisticsRepositoryFactory::DefaultStatisticsRepositoryFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<StatisticsRepository> DefaultStatisticsRepositoryFactory::createStatisticsRepository() const
{
    return std::make_unique<DefaultStatisticsRepository>(std::make_unique<StatisticsPersistentStorage>(
        fileAccess, std::make_shared<StatisticsJsonSerializer>()));
}
}