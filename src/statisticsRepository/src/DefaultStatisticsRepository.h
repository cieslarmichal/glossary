#pragma once

#include <memory>

#include "StatisticsRepository.h"
#include "StatisticsStorage.h"

namespace statisticsRepository
{
class DefaultStatisticsRepository : public StatisticsRepository
{
public:
    explicit DefaultStatisticsRepository(std::unique_ptr<StatisticsStorage>);

    boost::optional<WordStatistics> getWordStatistics(const EnglishWord&) const override;
    Statistics getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    void resetStatistics() override;

private:
    void addEmptyWordStatistics(const EnglishWord&) const;

    std::unique_ptr<StatisticsStorage> storage;
};
}
