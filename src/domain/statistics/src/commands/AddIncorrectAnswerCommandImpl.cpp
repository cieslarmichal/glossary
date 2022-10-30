#include "AddIncorrectAnswerCommandImpl.h"

namespace glossary::statistics
{
AddIncorrectAnswerCommandImpl::AddIncorrectAnswerCommandImpl(
    std::shared_ptr<StatisticsRepository> statisticsRepositoryInit)
    : statisticsRepository{std::move(statisticsRepositoryInit)}
{
}
void AddIncorrectAnswerCommandImpl::addIncorrectAnswer(const std::string& englishWord)
{
    statisticsRepository->addIncorrectAnswer(englishWord);
}
}
