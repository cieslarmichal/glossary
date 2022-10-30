#pragma once

#include <memory>

#include "../repositories/StatisticsRepository.h"
#include "queries/GetWordsStatisticsQuery.h"

namespace glossary::statistics
{
class GetWordsStatisticsQueryImpl : public GetWordsStatisticsQuery
{
public:
    explicit GetWordsStatisticsQueryImpl(std::shared_ptr<StatisticsRepository>);

    std::vector<WordStatistics> getWordsStatistics() override;

private:
    std::shared_ptr<StatisticsRepository> statisticsRepository;
};
}
