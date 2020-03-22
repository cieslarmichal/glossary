#pragma once

#include <ostream>
#include <vector>

#include "EnglishWord.h"

namespace statisticsRepository
{
class WordStatistics
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
    int amountOfCorrectAnswers;
    int amountOfIncorrectAnswers;
};

bool operator==(const WordStatistics& lhs, const WordStatistics& rhs);
std::ostream& operator<<(std::ostream& os, const WordStatistics& wordStatistics);
}
