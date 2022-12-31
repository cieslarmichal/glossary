#include "factories/StatisticsFactory.h"

#include "StatisticsFactoryImpl.h"

namespace glossary::statistics
{
std::unique_ptr<StatisticsFactory>
StatisticsFactory::createStatisticsFactory(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
{
    return std::make_unique<StatisticsFactoryImpl>(fileAccess);
}
}
