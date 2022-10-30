#pragma once

#include <memory>

#include "../repositories/StatisticsRepository.h"
#include "commands/AddCorrectAnswerCommand.h"

namespace glossary::statistics
{
class AddCorrectAnswerCommandImpl : public AddCorrectAnswerCommand
{
public:
    explicit AddCorrectAnswerCommandImpl(std::shared_ptr<StatisticsRepository>);

    void addCorrectAnswer(const std::string& englishWord) override;

private:
    std::shared_ptr<StatisticsRepository> statisticsRepository;
};
}
