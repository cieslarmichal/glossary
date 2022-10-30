#pragma once

#include <ostream>
#include <vector>

namespace glossary::statistics
{
struct WordStatistics
{
    std::string englishWord;
    int correctAnswers;
    int incorrectAnswers;
};

inline bool operator==(const WordStatistics& lhs, const WordStatistics& rhs)
{
    return (lhs.englishWord == rhs.englishWord && lhs.correctAnswers == rhs.correctAnswers &&
            lhs.incorrectAnswers == rhs.incorrectAnswers);
}

inline std::string toString(const WordStatistics& wordStatistics)
{
    return "{englishWord: " + wordStatistics.englishWord +
           ", correctAnswers: " + std::to_string(wordStatistics.correctAnswers) +
           ", incorrectAnswers: " + std::to_string(wordStatistics.incorrectAnswers) + "}";
}

inline std::ostream& operator<<(std::ostream& os, const WordStatistics& wordStatistics)
{
    return os << toString(wordStatistics);
}
}
