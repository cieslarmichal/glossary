#include "StatisticsRepositoryFactory.h"

#include "DefaultStatisticsRepositoryFactory.h"

namespace glossary::statisticsRepository
{
std::unique_ptr<StatisticsRepositoryFactory> StatisticsRepositoryFactory::createStatisticsRepositoryFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultStatisticsRepositoryFactory>(fileAccess);
}
}