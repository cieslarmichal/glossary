#pragma once

#include "StatisticsDbFactory.h"

namespace statisticsDb
{
class StatisticsDbFactoryImpl : public StatisticsDbFactory
{
public:
    explicit StatisticsDbFactoryImpl(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<StatisticsDb> createStatisticsDb() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}
