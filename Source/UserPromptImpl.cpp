#include "UserPromptImpl.h"

#include <iostream>

#include "StringHelper.h"
#include "boost/algorithm/string.hpp"

namespace
{
constexpr auto newLine{'\n'};
std::vector<std::string> correctYesNoAnswers{{"y", "yes", "n", "no"}};
}

UserInput UserPromptImpl::getInput() const
{
    return getValidString();
}

UserInput UserPromptImpl::yesPrompt() const
{
    std::string choice;
    while (!(std::cin >> choice) or yesNoAnswerIsInvalid(choice))
    {
        clearInputBuffer();
        std::cout << "Enter correct answer (y/n): ";
    }
    clearInputBuffer();

    return choice;
}

std::string UserPromptImpl::getValidString() const
{
    std::string temp;
    while (not(std::cin >> temp))
    {
        clearInputBuffer();
        std::cerr << "Enter valid string: ";
    }
    clearInputBuffer();
    return temp;
}

bool UserPromptImpl::yesNoAnswerIsInvalid(const std::string& input) const
{
    const auto isValid =
        std::any_of(correctYesNoAnswers.begin(), correctYesNoAnswers.end(),
                    [input](const auto& yesNo) {
                        return yesNo == stringHelper::getCaseInsensitive(input);
                    });

    return !isValid;
}

void UserPromptImpl::clearInputBuffer() const
{
    std::cin.clear();
    while (std::cin.get() != newLine)
    {
    }
}
