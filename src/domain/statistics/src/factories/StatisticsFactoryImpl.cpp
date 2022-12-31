#include "StatisticsFactoryImpl.h"

#include "../commands/AddCorrectAnswerCommandImpl.h"
#include "../commands/AddIncorrectAnswerCommandImpl.h"
#include "../commands/AddWordStatisticsCommandImpl.h"
#include "../commands/ResetWordsStatisticsCommandImpl.h"
#include "../queries/GetWordsStatisticsQueryImpl.h"
#include "../repositories/DefaultStatisticsRepository.h"
#include "../repositories/StatisticsPersistentStorage.h"
#include "../serializers/WordsStatisticsJsonSerializer.h"

namespace glossary::statistics
{

StatisticsFactoryImpl::StatisticsFactoryImpl(const std::shared_ptr<common::fileSystem::FileAccess>& fileAccess)
    : statisticsRepository{std::make_shared<DefaultStatisticsRepository>(
          std::make_unique<StatisticsPersistentStorage>(fileAccess, std::make_shared<WordsStatisticsJsonSerializer>()))}
{
}

std::unique_ptr<GetWordsStatisticsQuery> StatisticsFactoryImpl::createGetWordsStatisticsQuery() const
{
    return std::make_unique<GetWordsStatisticsQueryImpl>(statisticsRepository);
}

std::unique_ptr<AddCorrectAnswerCommand> StatisticsFactoryImpl::createAddCorrectAnswerCommand() const
{
    return std::make_unique<AddCorrectAnswerCommandImpl>(statisticsRepository);
}

std::unique_ptr<AddIncorrectAnswerCommand> StatisticsFactoryImpl::createAddIncorrectAnswerCommand() const
{
    return std::make_unique<AddIncorrectAnswerCommandImpl>(statisticsRepository);
}

std::unique_ptr<AddWordStatisticsCommand> StatisticsFactoryImpl::createAddWordStatisticsCommand() const
{
    return std::make_unique<AddWordStatisticsCommandImpl>(statisticsRepository);
}

std::unique_ptr<ResetWordsStatisticsCommand> StatisticsFactoryImpl::createResetWordsStatisticsCommand() const
{
    return std::make_unique<ResetWordsStatisticsCommandImpl>(statisticsRepository);
}
}
