#pragma once

#include <memory>

#include "../repositories/StatisticsRepository.h"
#include "commands/AddWordStatisticsCommand.h"

namespace glossary::statistics
{
class AddWordStatisticsCommandImpl : public AddWordStatisticsCommand
{
public:
    explicit AddWordStatisticsCommandImpl(std::shared_ptr<StatisticsRepository>);

    void addWordStatistics(const WordStatistics&) override;

private:
    std::shared_ptr<StatisticsRepository> statisticsRepository;
};
}
