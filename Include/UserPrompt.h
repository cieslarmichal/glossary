#pragma once

#include "UserInput.h"

class UserPrompt
{
public:
    virtual ~UserPrompt() = default;

    virtual UserInput getInput() const = 0;
};