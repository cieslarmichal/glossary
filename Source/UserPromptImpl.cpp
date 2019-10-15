#include "UserPromptImpl.h"

#include <iostream>

namespace
{
constexpr auto newLine{'\n'};
}

UserInput UserPromptImpl::getInput() const
{
    return getValidString();
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

void UserPromptImpl::clearInputBuffer() const
{
    std::cin.clear();
    while (std::cin.get() != newLine);
}
