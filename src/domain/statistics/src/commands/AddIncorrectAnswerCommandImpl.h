#pragma once

#include <memory>

#include "../repositories/StatisticsRepository.h"
#include "commands/AddIncorrectAnswerCommand.h"

namespace glossary::statistics
{
class AddIncorrectAnswerCommandImpl : public AddIncorrectAnswerCommand
{
public:
    explicit AddIncorrectAnswerCommandImpl(std::shared_ptr<StatisticsRepository>);

    void addIncorrectAnswer(const std::string& englishWord) override;

private:
    std::shared_ptr<StatisticsRepository> statisticsRepository;
};
}
