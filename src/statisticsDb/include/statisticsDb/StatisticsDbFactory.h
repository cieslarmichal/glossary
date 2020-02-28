#pragma once

#include <memory>

#include "StatisticsDb.h"
#include "utils/FileAccess.h"

namespace statisticsDb
{
class StatisticsDbFactory
{
public:
    virtual ~StatisticsDbFactory() = default;

    virtual std::unique_ptr<StatisticsDb> createStatisticsDb() const = 0;

    static std::unique_ptr<StatisticsDbFactory>
    createStatisticsDbFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}