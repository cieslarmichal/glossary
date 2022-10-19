#pragma once

#include <ostream>
#include <vector>

namespace glossary::statistics
{
class WordStatistics
{
public:
    WordStatistics(std::string);
    WordStatistics(std::string, int amountOfCorrectAnswers, int amountOfIncorrectAnswers);

    void addCorrectAnswer();
    void addIncorrectAnswer();
    void resetAnswers();
    std::string getEnglishWord() const;
    int getAmountOfCorrectAnswers() const;
    int getAmountOfIncorrectAnswers() const;

private:
    std::string englishWord;
    int correctAnswers;
    int incorrectAnswers;
};

bool operator==(const WordStatistics& lhs, const WordStatistics& rhs);
std::string toString(const WordStatistics&);
std::ostream& operator<<(std::ostream& os, const WordStatistics& wordStatistics);
}
