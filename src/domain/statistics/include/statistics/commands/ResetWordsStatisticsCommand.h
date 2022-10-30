#pragma once

#include <string>

namespace glossary::statistics
{
class ResetWordsStatisticsCommand
{
public:
    virtual ~ResetWordsStatisticsCommand() = default;

    virtual void resetWordsStatistics() = 0;
};
}
