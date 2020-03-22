#pragma once

#include "gmock/gmock.h"

#include "StatisticsModifierService.h"

class StatisticsModifierServiceMock : public StatisticsModifierService
{
public:
    MOCK_METHOD1(addCorrectAnswer, void(const statisticsRepository::EnglishWord&));
    MOCK_METHOD1(addIncorrectAnswer, void(const statisticsRepository::EnglishWord&));
};
