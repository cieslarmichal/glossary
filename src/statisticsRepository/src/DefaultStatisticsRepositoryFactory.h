#pragma once

#include "StatisticsRepositoryFactory.h"

namespace statisticsRepository
{
class DefaultStatisticsRepositoryFactory : public StatisticsRepositoryFactory
{
public:
    explicit DefaultStatisticsRepositoryFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<StatisticsRepository> createStatisticsRepository() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}
