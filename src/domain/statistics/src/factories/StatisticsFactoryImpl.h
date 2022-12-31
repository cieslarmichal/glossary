#pragma once

#include <memory>

#include "../repositories/StatisticsRepository.h"
#include "factories/StatisticsFactory.h"
#include "fileSystem/FileAccess.h"

namespace glossary::statistics
{
class StatisticsFactoryImpl : public StatisticsFactory
{
public:
    StatisticsFactoryImpl(const std::shared_ptr<common::fileSystem::FileAccess>&);

    std::unique_ptr<GetWordsStatisticsQuery> createGetWordsStatisticsQuery() const override;
    std::unique_ptr<AddCorrectAnswerCommand> createAddCorrectAnswerCommand() const override;
    std::unique_ptr<AddIncorrectAnswerCommand> createAddIncorrectAnswerCommand() const override;
    std::unique_ptr<AddWordStatisticsCommand> createAddWordStatisticsCommand() const override;
    std::unique_ptr<ResetWordsStatisticsCommand> createResetWordsStatisticsCommand() const override;

private:
    std::shared_ptr<StatisticsRepository> statisticsRepository;
};
}
