#pragma once

#include <optional>

#include "WordStatistics.h"

namespace glossary::statistics
{
class StatisticsRepository
{
public:
    virtual ~StatisticsRepository() = default;

    virtual std::optional<WordStatistics> getWordStatistics(const std::string&) const = 0;
    virtual std::vector<WordStatistics> getStatistics() const = 0;
    virtual void addWordStatistics(WordStatistics) = 0;
    virtual void addCorrectAnswer(const std::string&) = 0;
    virtual void addIncorrectAnswer(const std::string&) = 0;
    virtual void resetStatistics() = 0;
};
}
