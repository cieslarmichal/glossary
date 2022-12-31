#pragma once

#include <memory>

#include "../commands/AddCorrectAnswerCommand.h"
#include "../commands/AddIncorrectAnswerCommand.h"
#include "../commands/AddWordStatisticsCommand.h"
#include "../commands/ResetWordsStatisticsCommand.h"
#include "../queries/GetWordsStatisticsQuery.h"
#include "fileSystem/FileAccess.h"

namespace glossary::statistics
{
class StatisticsFactory
{
public:
    virtual ~StatisticsFactory() = default;

    virtual std::unique_ptr<GetWordsStatisticsQuery> createGetWordsStatisticsQuery() const = 0;
    virtual std::unique_ptr<AddCorrectAnswerCommand> createAddCorrectAnswerCommand() const = 0;
    virtual std::unique_ptr<AddIncorrectAnswerCommand> createAddIncorrectAnswerCommand() const = 0;
    virtual std::unique_ptr<AddWordStatisticsCommand> createAddWordStatisticsCommand() const = 0;
    virtual std::unique_ptr<ResetWordsStatisticsCommand> createResetWordsStatisticsCommand() const = 0;

    static std::unique_ptr<StatisticsFactory>
    createStatisticsFactory(const std::shared_ptr<common::fileSystem::FileAccess>&);
};
}
