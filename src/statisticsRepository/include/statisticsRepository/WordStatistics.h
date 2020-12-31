#pragma once

#include <ostream>
#include <vector>

#include "EnglishWord.h"
#include "StatisticsRepositoryApi.h"

namespace glossary::statisticsRepository
{
class STATISTICS_REPOSITORY_API WordStatistics
{
public:
    WordStatistics(EnglishWord);
    WordStatistics(EnglishWord, int amountOfCorrectAnswers, int amountOfIncorrectAnswers);

    void addCorrectAnswer();
    void addIncorrectAnswer();
    void resetAnswers();
    EnglishWord getEnglishWord() const;
    int getAmountOfCorrectAnswers() const;
    int getAmountOfIncorrectAnswers() const;

private:
    EnglishWord englishWord;
    int correctAnswers;
    int incorrectAnswers;
};

STATISTICS_REPOSITORY_API bool operator==(const WordStatistics& lhs, const WordStatistics& rhs);
STATISTICS_REPOSITORY_API std::string toString(const WordStatistics&);
STATISTICS_REPOSITORY_API std::ostream& operator<<(std::ostream& os, const WordStatistics& wordStatistics);
}
