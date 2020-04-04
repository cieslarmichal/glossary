#include "DefaultAnswerValidator.h"

#include "boost/algorithm/string.hpp"

#include "utils/StringHelper.h"

namespace glossary
{
namespace
{
std::vector<std::string> correctYesAnswers{{"y"}, {"yes"}};
}

bool DefaultAnswerValidator::validateAnswer(const std::string& userInput,
                                            const std::string& expectedAnswer) const
{
    return utils::getLowerCases(userInput) == utils::getLowerCases(expectedAnswer);
}

bool DefaultAnswerValidator::validateYesAnswer(const std::string& userInput) const
{
    const auto isYesAnswer =
        std::any_of(correctYesAnswers.begin(), correctYesAnswers.end(),
                    [userInput](const auto& yes) { return yes == utils::getLowerCases(userInput); });

    return isYesAnswer;
}
}