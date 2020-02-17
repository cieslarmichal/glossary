#include "StatisticsDbFactoryImpl.h"

#include "StatisticsDbImpl.h"
#include "StatisticsPersistentStorage.h"
#include "StatisticsSerializerImpl.h"

namespace statisticsDb
{

StatisticsDbFactoryImpl::StatisticsDbFactoryImpl(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<StatisticsDb>
StatisticsDbFactoryImpl::createStatisticsDb() const
{
    return std::make_unique<StatisticsDbImpl>(
        std::make_unique<StatisticsPersistentStorage>(
            fileAccess, std::make_shared<StatisticsSerializerImpl>()));
}
}