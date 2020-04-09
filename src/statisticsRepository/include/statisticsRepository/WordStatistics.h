#pragma once

#include <ostream>
#include <vector>

#include "EnglishWord.h"

namespace glossary::statisticsRepository
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
    int correctAnswers;
    int incorrectAnswers;
};

bool operator==(const WordStatistics& lhs, const WordStatistics& rhs);
std::string toString(const WordStatistics&);
std::ostream& operator<<(std::ostream& os, const WordStatistics& wordStatistics);
}
