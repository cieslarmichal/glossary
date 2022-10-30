#pragma once

#include "StatisticsStorage.h"

namespace glossary::statistics
{
class StatisticsMemoryStorage : public StatisticsStorage
{
public:
    std::optional<WordStatistics> getWordStatistics(const std::string&) const override;
    std::vector<WordStatistics> getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const std::string&) override;
    void addIncorrectAnswer(const std::string&) override;
    void resetStatistics() override;
    bool contains(const std::string&) const override;
    std::vector<WordStatistics>::size_type size() const override;
    bool empty() const override;

private:
    std::vector<WordStatistics>::const_iterator findWordStatisticsPosition(const std::string&) const;

    std::vector<WordStatistics> statistics;
};
}