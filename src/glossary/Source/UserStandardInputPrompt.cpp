#include "UserStandardInputPrompt.h"

#include <iostream>

#include "boost/algorithm/string.hpp"

#include "utils/StringHelper.h"

namespace glossary
{
namespace
{
constexpr auto newLine{'\n'};
}

std::string UserStandardInputPrompt::getStringInput() const
{
    return getValidString();
}

int UserStandardInputPrompt::getNumberInput() const
{
    return getValidInt();
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

int UserStandardInputPrompt::getValidInt() const
{
    int temp;
    while (not(std::cin >> temp))
    {
        clearInputBuffer();
        std::cerr << "Enter valid number: ";
    }
    clearInputBuffer();
    return temp;
}

void UserStandardInputPrompt::clearInputBuffer() const
{
    std::cin.clear();
    while (std::cin.get() != newLine)
    {
    }
}
}
