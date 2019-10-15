#include "AnswerCheckerImpl.h"

#include "boost/algorithm/string.hpp"

bool AnswerCheckerImpl::checkAnswer(const UserInput& input, const EnglishWord& englishWord) const
{
    return areEqual(input, englishWord);
}

bool AnswerCheckerImpl::areEqual(const UserInput& input, const EnglishWord& englishWord) const
{
    const auto inputCaseInsensitive = boost::algorithm::to_lower_copy(input);
    const auto englishWordCaseInsensitive = boost::algorithm::to_lower_copy(englishWord);

    return inputCaseInsensitive == englishWordCaseInsensitive;
}
