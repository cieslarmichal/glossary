#pragma once

#include "UserInput.h"

namespace glossary
{
class UserPrompt
{
public:
    virtual ~UserPrompt() = default;

    virtual UserInput getStringInput() const = 0;
    virtual int getIntInput() const = 0;
    virtual UserInput yesPrompt() const = 0;
};
}