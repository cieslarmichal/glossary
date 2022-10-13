#include "WordStatistics.h"

namespace glossary::statistics
{

WordStatistics::WordStatistics(std::string word) : englishWord{std::move(word)}
{
    resetAnswers();
}

WordStatistics::WordStatistics(std::string word, int correctAnswers, int incorrectAnswers)
    : englishWord{std::move(word)}, correctAnswers{correctAnswers}, incorrectAnswers{incorrectAnswers}
{
}

void WordStatistics::addCorrectAnswer()
{
    correctAnswers++;
}

void WordStatistics::addIncorrectAnswer()
{
    incorrectAnswers++;
}

void WordStatistics::resetAnswers()
{
    correctAnswers = 0;
    incorrectAnswers = 0;
}

std::string WordStatistics::getEnglishWord() const
{
    return englishWord;
}

int WordStatistics::getAmountOfCorrectAnswers() const
{
    return correctAnswers;
}

int WordStatistics::getAmountOfIncorrectAnswers() const
{
    return incorrectAnswers;
}

bool operator==(const WordStatistics& lhs, const WordStatistics& rhs)
{
    return (lhs.getEnglishWord() == rhs.getEnglishWord() &&
            lhs.getAmountOfCorrectAnswers() == rhs.getAmountOfCorrectAnswers() &&
            lhs.getAmountOfIncorrectAnswers() == rhs.getAmountOfIncorrectAnswers());
}

std::string toString(const WordStatistics& wordStatistics)
{
    return "{englishWord:" + wordStatistics.getEnglishWord() +
           ",correctAnswers:" + std::to_string(wordStatistics.getAmountOfCorrectAnswers()) +
           ",incorrectAnswers:" + std::to_string(wordStatistics.getAmountOfIncorrectAnswers()) + "}";
}

std::ostream& operator<<(std::ostream& os, const WordStatistics& wordStatistics)
{
    return os << toString(wordStatistics);
}

}