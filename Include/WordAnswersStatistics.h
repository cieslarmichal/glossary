#pragma once

#include <ostream>
#include "EnglishWord.h"

struct WordAnswersStatistics
{
    EnglishWord englishWord;
    int correctAnswers;
    int incorrectAnswers;
};

inline bool operator==(const WordAnswersStatistics& lhs, const WordAnswersStatistics& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.correctAnswers == rhs.correctAnswers &&
            lhs.incorrectAnswers == rhs.incorrectAnswers);
}

inline std::ostream& operator<<(std::ostream& os, const WordAnswersStatistics& wordAnswersStatistics)
{
    os << wordAnswersStatistics.englishWord << " " << wordAnswersStatistics.correctAnswers << " "
       << wordAnswersStatistics.incorrectAnswers;
    return os;
}
