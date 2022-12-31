#pragma once

#include <string>

#include "../WordStatistics.h"

namespace glossary::statistics
{
class AddWordStatisticsCommand
{
public:
    virtual ~AddWordStatisticsCommand() = default;

    virtual void addWordStatistics(const WordStatistics&) = 0;
};
}
