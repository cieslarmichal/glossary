#include "WordStatistics.h"

namespace glossary::statisticsRepository
{

WordStatistics::WordStatistics(EnglishWord word) : englishWord{std::move(word)}
{
    resetAnswers();
}

WordStatistics::WordStatistics(EnglishWord word, int correctAnswers, int incorrectAnswers)
    : englishWord{std::move(word)},
      amountOfCorrectAnswers{correctAnswers},
      amountOfIncorrectAnswers{incorrectAnswers}
{
}

void WordStatistics::addCorrectAnswer()
{
    amountOfCorrectAnswers++;
}

void WordStatistics::addIncorrectAnswer()
{
    amountOfIncorrectAnswers++;
}

void WordStatistics::resetAnswers()
{
    amountOfCorrectAnswers = 0;
    amountOfIncorrectAnswers = 0;
}

EnglishWord WordStatistics::getEnglishWord() const
{
    return englishWord;
}

int WordStatistics::getAmountOfCorrectAnswers() const
{
    return amountOfCorrectAnswers;
}

int WordStatistics::getAmountOfIncorrectAnswers() const
{
    return amountOfIncorrectAnswers;
}

bool operator==(const WordStatistics& lhs, const WordStatistics& rhs)
{
    return (lhs.getEnglishWord() == rhs.getEnglishWord() &&
            lhs.getAmountOfCorrectAnswers() == rhs.getAmountOfCorrectAnswers() &&
            lhs.getAmountOfIncorrectAnswers() == rhs.getAmountOfIncorrectAnswers());
}

std::ostream& operator<<(std::ostream& os, const WordStatistics& wordStatistics)
{
    os << wordStatistics.getEnglishWord() << " " << wordStatistics.getAmountOfCorrectAnswers() << " "
       << wordStatistics.getAmountOfIncorrectAnswers();
    return os;
}

}