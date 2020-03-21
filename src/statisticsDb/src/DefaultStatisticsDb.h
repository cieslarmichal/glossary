#pragma once

#include <memory>

#include "StatisticsDb.h"
#include "StatisticsStorage.h"

namespace statisticsDb
{

class DefaultStatisticsDb : public StatisticsDb
{
public:
    explicit DefaultStatisticsDb(std::unique_ptr<StatisticsStorage>);

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
