#pragma once

#include <memory>

#include "StatisticsModifierService.h"
#include "statisticsRepository/StatisticsRepository.h"

class DefaultStatisticsModifierService : public StatisticsModifierService
{
public:
    explicit DefaultStatisticsModifierService(std::shared_ptr<statisticsRepository::StatisticsRepository>);

    void addCorrectAnswer(const statisticsRepository::EnglishWord&) override;
    void addIncorrectAnswer(const statisticsRepository::EnglishWord&) override;

private:
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepository;
};