#include "AnswerCheckerImpl.h"

#include "StringHelper.h"
#include "boost/algorithm/string.hpp"

namespace
{
std::vector<std::string> correctYesAnswers{{"y"}, {"yes"}};

}

bool AnswerCheckerImpl::correctWordAnswer(const UserInput& userInput, const EnglishWord& englishWord) const
{
    return stringHelper::getCaseInsensitive(userInput) == stringHelper::getCaseInsensitive(englishWord);
}

bool AnswerCheckerImpl::yesAnswer(const UserInput& userInput) const
{
    const auto isYesAnswer = std::any_of(correctYesAnswers.begin(), correctYesAnswers.end(),
                                         [userInput](const auto& yes)
                                         { return yes == stringHelper::getCaseInsensitive(userInput); });

    return isYesAnswer;

}
