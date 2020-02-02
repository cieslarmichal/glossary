#include "AnswerCheckerImpl.h"

#include "PolishWord.h"
#include "StringHelper.h"
#include "boost/algorithm/string.hpp"

namespace
{
std::vector<std::string> correctYesAnswers{{"y"}, {"yes"}};

}

bool AnswerCheckerImpl::correctWordAnswer(const UserInput& userInput,
                                          const PolishWord& polishWord) const
{
    return stringHelper::getLowerCases(userInput) ==
           stringHelper::getLowerCases(polishWord);
}

bool AnswerCheckerImpl::yesAnswer(const UserInput& userInput) const
{
    const auto isYesAnswer = std::any_of(
        correctYesAnswers.begin(), correctYesAnswers.end(),
        [userInput](const auto& yes) {
            return yes == stringHelper::getLowerCases(userInput);
        });

    return isYesAnswer;
}
