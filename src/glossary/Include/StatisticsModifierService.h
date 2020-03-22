#pragma once

#include "statisticsRepository/EnglishWord.h"

class StatisticsModifierService
{
public:
    virtual ~StatisticsModifierService() = default;

    virtual void addCorrectAnswer(const statisticsRepository::EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const statisticsRepository::EnglishWord&) = 0;
};