#include "StatisticsDbFactory.h"

#include "StatisticsDbFactoryImpl.h"

namespace statisticsDb
{

std::unique_ptr<StatisticsDbFactory>
StatisticsDbFactory::createStatisticsDbFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<StatisticsDbFactoryImpl>(fileAccess);
}
}