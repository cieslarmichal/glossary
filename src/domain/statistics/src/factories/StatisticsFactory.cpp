#include "factories/StatisticsFactory.h"

#include "StatisticsFactoryImpl.h"

namespace glossary::statistics
{
std::unique_ptr<StatisticsFactory> StatisticsFactory::createStatisticsFactory()
{
    return std::make_unique<StatisticsFactoryImpl>();
}
}
