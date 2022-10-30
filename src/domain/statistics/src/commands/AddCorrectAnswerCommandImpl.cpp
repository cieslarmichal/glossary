#include "AddCorrectAnswerCommandImpl.h"

namespace glossary::statistics
{
AddCorrectAnswerCommandImpl::AddCorrectAnswerCommandImpl(std::shared_ptr<StatisticsRepository> statisticsRepositoryInit)
    : statisticsRepository{std::move(statisticsRepositoryInit)}
{
}
void AddCorrectAnswerCommandImpl::addCorrectAnswer(const std::string& englishWord)
{
    statisticsRepository->addCorrectAnswer(englishWord);
}
}
