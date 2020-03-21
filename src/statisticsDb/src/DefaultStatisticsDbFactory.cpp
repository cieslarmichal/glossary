#include "DefaultStatisticsDbFactory.h"

#include "DefaultStatisticsDb.h"
#include "StatisticsJsonSerializer.h"
#include "StatisticsPersistentStorage.h"

namespace statisticsDb
{

DefaultStatisticsDbFactory::DefaultStatisticsDbFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<StatisticsDb> DefaultStatisticsDbFactory::createStatisticsDb() const
{
    return std::make_unique<DefaultStatisticsDb>(std::make_unique<StatisticsPersistentStorage>(
        fileAccess, std::make_shared<StatisticsJsonSerializer>()));
}
}