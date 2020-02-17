#include "AnswerCheckerImpl.h"

#include "PolishWord.h"
#include "boost/algorithm/string.hpp"
#include "utils/StringHelper.h"

namespace
{
std::vector<std::string> correctYesAnswers{{"y"}, {"yes"}};
}

bool AnswerCheckerImpl::correctWordAnswer(const UserInput& userInput,
                                          const PolishWord& polishWord) const
{
    return utils::getLowerCases(userInput) == utils::getLowerCases(polishWord);
}

bool AnswerCheckerImpl::yesAnswer(const UserInput& userInput) const
{
    const auto isYesAnswer =
        std::any_of(correctYesAnswers.begin(), correctYesAnswers.end(),
                    [userInput](const auto& yes) {
                        return yes == utils::getLowerCases(userInput);
                    });

    return isYesAnswer;
}
