#include "StatisticsDbFactory.h"

#include "DefaultStatisticsDbFactory.h"

namespace statisticsDb
{

std::unique_ptr<StatisticsDbFactory>
StatisticsDbFactory::createStatisticsDbFactory(const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultStatisticsDbFactory>(fileAccess);
}
}