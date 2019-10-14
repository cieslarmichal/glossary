#pragma once

#include <ostream>
#include "EnglishWord.h"

struct AnswersStatisticsPerWord
{
    void addCorrectAnswer()
    {
        correctAnswers++;
    }

    void addIncorrectAnswer()
    {
        incorrectAnswers++;
    }

    EnglishWord englishWord;
    int correctAnswers{0};
    int incorrectAnswers{0};
};

inline bool operator==(const AnswersStatisticsPerWord& lhs, const AnswersStatisticsPerWord& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.correctAnswers == rhs.correctAnswers &&
            lhs.incorrectAnswers == rhs.incorrectAnswers);
}

inline std::ostream& operator<<(std::ostream& os, const AnswersStatisticsPerWord& wordAnswersStatistics)
{
    os << wordAnswersStatistics.englishWord << " " << wordAnswersStatistics.correctAnswers << " "
       << wordAnswersStatistics.incorrectAnswers;
    return os;
}
