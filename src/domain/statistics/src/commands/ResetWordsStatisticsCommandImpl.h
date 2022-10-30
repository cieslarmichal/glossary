#pragma once

#include <memory>

#include "../repositories/StatisticsRepository.h"
#include "commands/ResetWordsStatisticsCommand.h"

namespace glossary::statistics
{
class ResetWordsStatisticsCommandImpl : public ResetWordsStatisticsCommand
{
public:
    explicit ResetWordsStatisticsCommandImpl(std::shared_ptr<StatisticsRepository>);

    void resetWordsStatistics() override;

private:
    std::shared_ptr<StatisticsRepository> statisticsRepository;
};
}
