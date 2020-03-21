#include "UserStandardInputPrompt.h"

#include <iostream>

#include "boost/algorithm/string.hpp"

#include "utils/StringHelper.h"

namespace
{
constexpr auto newLine{'\n'};
std::vector<std::string> correctYesNoAnswers{{"y", "yes", "n", "no"}};
}

UserInput UserStandardInputPrompt::getInput() const
{
    return getValidString();
}

UserInput UserStandardInputPrompt::yesPrompt() const
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

std::string UserStandardInputPrompt::getValidString() const
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

bool UserStandardInputPrompt::yesNoAnswerIsInvalid(const std::string& input) const
{
    const auto isValid =
        std::any_of(correctYesNoAnswers.begin(), correctYesNoAnswers.end(),
                    [input](const auto& yesNo) { return yesNo == utils::getLowerCases(input); });

    return !isValid;
}

void UserStandardInputPrompt::clearInputBuffer() const
{
    std::cin.clear();
    while (std::cin.get() != newLine)
    {
    }
}
