#include "DefaultStatisticsModifierService.h"

DefaultStatisticsModifierService::DefaultStatisticsModifierService(
    std::shared_ptr<statisticsRepository::StatisticsRepository> statisticsRepositoryInit)
    : statisticsRepository{std::move(statisticsRepositoryInit)}
{
}

void DefaultStatisticsModifierService::addCorrectAnswer(const statisticsRepository::EnglishWord& englishWord)
{
    statisticsRepository->addCorrectAnswer(englishWord);
}

void DefaultStatisticsModifierService::addIncorrectAnswer(
    const statisticsRepository::EnglishWord& englishWord)
{
    statisticsRepository->addIncorrectAnswer(englishWord);
}
