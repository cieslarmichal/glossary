#pragma once

#include "gmock/gmock.h"

#include "AddWordStatisticsCommand.h"

namespace glossary::statistics
{
class AddWordStatisticsCommandMock : public AddWordStatisticsCommand
{
public:
    MOCK_METHOD(void, addWordStatistics, (const WordStatistics&), ());
};
}
