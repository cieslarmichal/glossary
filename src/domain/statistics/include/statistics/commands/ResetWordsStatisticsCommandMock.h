#pragma once

#include "gmock/gmock.h"

#include "ResetWordsStatisticsCommand.h"

namespace glossary::statistics
{
class ResetWordsStatisticsCommandMock : public ResetWordsStatisticsCommand
{
public:
    MOCK_METHOD(void, resetWordsStatistics, (), ());
};
}
