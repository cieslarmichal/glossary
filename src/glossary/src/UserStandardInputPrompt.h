#pragma once

#include "UserPrompt.h"

namespace glossary
{
class UserStandardInputPrompt : public UserPrompt
{
public:
    std::string getStringInput() const override;
    int getNumberInput() const override;

private:
    std::string getValidString() const;
    int getValidInt() const;
    void clearInputBuffer() const;
};
}