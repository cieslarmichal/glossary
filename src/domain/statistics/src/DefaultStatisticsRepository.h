#pragma once

#include <memory>

#include "StatisticsRepository.h"
#include "StatisticsStorage.h"

namespace glossary::statistics
{
class DefaultStatisticsRepository : public StatisticsRepository
{
public:
    explicit DefaultStatisticsRepository(std::unique_ptr<StatisticsStorage>);

    std::optional<WordStatistics> getWordStatistics(const std::string&) const override;
    std::vector<WordStatistics> getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const std::string&) override;
    void addIncorrectAnswer(const std::string&) override;
    void resetStatistics() override;

private:
    void addEmptyWordStatistics(const std::string&) const;

    std::unique_ptr<StatisticsStorage> storage;
};
}
