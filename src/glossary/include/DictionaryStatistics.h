#pragma once

#include <ostream>
#include <vector>

#include "dictionaryService/std::string.h"

namespace glossary
{
struct DictionaryStatistics
{
    dictionary::std::string dictionaryName;
    unsigned correctAnswers;
    unsigned incorrectAnswers;
};

using DictionariesStatistics = std::vector<DictionaryStatistics>;

inline bool operator==(const DictionaryStatistics& lhs, const DictionaryStatistics& rhs)
{
    return lhs.dictionaryName == rhs.dictionaryName && lhs.correctAnswers == rhs.correctAnswers &&
           lhs.incorrectAnswers == rhs.incorrectAnswers;
}

inline std::string toString(const DictionaryStatistics& dictionaryStatistics)
{
    return "{dictionaryName:" + dictionaryStatistics.dictionaryName +
           ",correctAnswers:" + std::to_string(dictionaryStatistics.correctAnswers) +
           ",incorrectAnswers:" + std::to_string(dictionaryStatistics.incorrectAnswers) + "}";
}

inline std::ostream& operator<<(std::ostream& os, const DictionaryStatistics& dictionaryStatistics)
{
    return os << toString(dictionaryStatistics);
}
}