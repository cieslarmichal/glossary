#pragma once

#include "UserPrompt.h"
#include <iostream>

class UserPromptImpl : public UserPrompt
{
public:
    UserInput getInput() const override;

private:
    std::string getValidString() const;
    void clearInputBuffer() const;
};